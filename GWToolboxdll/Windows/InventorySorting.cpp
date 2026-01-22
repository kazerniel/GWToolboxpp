#include "stdafx.h"

#include <Modules/Resources.h>
#include <Windows/InventorySorting.h>

#include <GWCA/Constants/Constants.h>

#include <GWCA/Managers/GameThreadMgr.h>
#include <GWCA/Managers/ItemMgr.h>
#include <GWCA/Managers/MapMgr.h>
#include <GWCA/Managers/MemoryMgr.h>

#include <GWCA/GameEntities/Item.h>

#include <Logger.h>
#include <Utils/GuiUtils.h>

#include <algorithm>
#include <chrono>
#include <sstream>
#include <thread>


namespace {
// Macro to wait for a game thread task to complete with timeout and cancellation checks
#define WAIT_FOR_GAME_THREAD_TASK(task_done_flag, timeout_ms, error_message)                \
    for (size_t i = 0; i < (timeout_ms) && !(task_done_flag) && !pending_cancel; i += 5) { \
        Sleep(5);                                                                          \
    }                                                                                       \
    if (!(task_done_flag)) {                                                                \
        Log::Warning(error_message);                                                        \
        is_sorting = false;                                                                 \
        show_sort_popup = false;                                                            \
        return;                                                                             \
    }                                                                                       \
    if (pending_cancel) {                                                                   \
        Log::Info("Sorting cancelled");                                                     \
        is_sorting = false;                                                                 \
        show_sort_popup = false;                                                            \
        return;                                                                             \
    }

    // Helper function to check if map is ready
    bool IsMapReady()
    {
        return GW::Map::GetInstanceType() != GW::Constants::InstanceType::Loading && !GW::Map::GetIsObserving() && GW::MemoryMgr::GetGWWindowHandle() == GetActiveWindow();
    }

    // ImGui colors for item rarities
    const ImVec4 ItemBlue = ImColor(153, 238, 255).Value;
    const ImVec4 ItemPurple = ImColor(187, 137, 237).Value;
    const ImVec4 ItemGold = ImColor(255, 204, 86).Value;

    // State variables
    bool show_sort_popup = false;
    bool is_sorting = false;
    bool pending_cancel = false;
    size_t items_sorted_count = 0;

    // Sort order configuration
    std::vector<GW::Constants::ItemType> sort_order;

    /**
     * Gets the sort priority for an item type (lower = higher priority).
     */
    uint32_t GetItemTypeSortPriority(GW::Constants::ItemType type)
    {
        for (size_t i = 0; i < sort_order.size(); i++) {
            if (sort_order[i] == type) {
                return static_cast<int>(i);
            }
        }
        return 9999; // Unknown types go to the end
    }
    /**
     * Draws the inventory sorting progress popup with cancel button.
     */
    void DrawSortInventoryPopup();


    /**
     * Gets the display name for an item type.
     */
    const char* GetItemTypeName(GW::Constants::ItemType type)
    {
        switch (type) {
            case GW::Constants::ItemType::Salvage:
                return "Salvage Kits";
            case GW::Constants::ItemType::Materials_Zcoins:
                return "Materials";
            case GW::Constants::ItemType::Trophy:
                return "Trophies";
            case GW::Constants::ItemType::Dye:
                return "Dyes";
            case GW::Constants::ItemType::Rune_Mod:
                return "Runes/Mods";
            case GW::Constants::ItemType::CC_Shards:
                return "Consets";
            case GW::Constants::ItemType::Usable:
                return "Consumables";
            case GW::Constants::ItemType::Key:
                return "Keys";
            case GW::Constants::ItemType::Axe:
                return "Axes";
            case GW::Constants::ItemType::Sword:
                return "Swords";
            case GW::Constants::ItemType::Hammer:
                return "Hammers";
            case GW::Constants::ItemType::Bow:
                return "Bows";
            case GW::Constants::ItemType::Staff:
                return "Staves";
            case GW::Constants::ItemType::Wand:
                return "Wands";
            case GW::Constants::ItemType::Offhand:
                return "Offhands";
            case GW::Constants::ItemType::Daggers:
                return "Daggers";
            case GW::Constants::ItemType::Scythe:
                return "Scythes";
            case GW::Constants::ItemType::Spear:
                return "Spears";
            case GW::Constants::ItemType::Shield:
                return "Shields";
            case GW::Constants::ItemType::Headpiece:
                return "Headpieces";
            case GW::Constants::ItemType::Chestpiece:
                return "Chestpieces";
            case GW::Constants::ItemType::Leggings:
                return "Leggings";
            case GW::Constants::ItemType::Boots:
                return "Boots";
            case GW::Constants::ItemType::Gloves:
                return "Gloves";
            default:
                return "Unknown";
        }
    }


    /**
     * Resets the sort order to default values.
     */
    void ResetSortOrder()
    {
        sort_order = {GW::Constants::ItemType::Salvage,    GW::Constants::ItemType::Materials_Zcoins,
                      GW::Constants::ItemType::Trophy,     GW::Constants::ItemType::Dye,
                      GW::Constants::ItemType::Rune_Mod,   GW::Constants::ItemType::CC_Shards,
                      GW::Constants::ItemType::Usable,     GW::Constants::ItemType::Key,
                      GW::Constants::ItemType::Axe,        GW::Constants::ItemType::Sword,
                      GW::Constants::ItemType::Hammer,     GW::Constants::ItemType::Bow,
                      GW::Constants::ItemType::Staff,      GW::Constants::ItemType::Wand,
                      GW::Constants::ItemType::Offhand,    GW::Constants::ItemType::Daggers,
                      GW::Constants::ItemType::Scythe,     GW::Constants::ItemType::Spear,
                      GW::Constants::ItemType::Shield,     GW::Constants::ItemType::Headpiece,
                      GW::Constants::ItemType::Chestpiece, GW::Constants::ItemType::Leggings,
                      GW::Constants::ItemType::Boots,      GW::Constants::ItemType::Gloves};
    }

    void DrawSortInventoryPopup()
    {
        if (show_sort_popup) {
            ImGui::OpenPopup("Sort Inventory");
        }

        if (ImGui::BeginPopupModal("Sort Inventory", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            if (!is_sorting) {
                // Sorting has completed, close the popup
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return;
            }

            ImGui::TextUnformatted("Sorting inventory by type...");
            ImGui::Text("Items sorted: %zu", items_sorted_count);

            ImGui::Separator();
            ImGui::Spacing();

            ImGui::TextDisabled("This may take a while depending on the number of items.");
            ImGui::TextDisabled("You can cancel at any time.");

            ImGui::Spacing();

            const float button_width = 120.0f;
            const float window_width = ImGui::GetContentRegionAvail().x;
            ImGui::SetCursorPosX((window_width - button_width) * 0.5f);

            if (ImGui::Button("Cancel", ImVec2(button_width, 0)) || ImGui::IsKeyPressed(ImGuiKey_Escape)) {
                pending_cancel = true;
                InventorySorting::CancelSort();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
} // namespace

void InventorySorting::Initialize()
{
    ToolboxUIElement::Initialize();

    // Initialize default sort order
    ResetSortOrder();
}

void InventorySorting::Terminate()
{
    ToolboxUIElement::Terminate();
    CancelSort();
}

void InventorySorting::Update(float)
{
    // Nothing to update in main thread
    // Worker thread handles all sorting logic
}

void InventorySorting::Draw(IDirect3DDevice9*)
{
    if (!GW::Map::GetIsMapLoaded()) {
        return;
    }

    DrawSortInventoryPopup();
}

void InventorySorting::LoadSettings(ToolboxIni* ini)
{
    ToolboxUIElement::LoadSettings(ini);

    // Load sort order
    const std::string sort_order_str = ini->GetValue(Name(), "sort_order", "");
    if (!sort_order_str.empty()) {
        sort_order.clear();
        std::stringstream ss(sort_order_str);
        std::string item;
        while (std::getline(ss, item, ',')) {
            try {
                const int type_val = std::stoi(item);
                sort_order.push_back(static_cast<GW::Constants::ItemType>(type_val));
            } catch (...) {
                // Invalid value, skip
            }
        }
    }

    // Fallback to default if empty
    if (sort_order.empty()) {
        ResetSortOrder();
    }
}

void InventorySorting::SaveSettings(ToolboxIni* ini)
{
    ToolboxUIElement::SaveSettings(ini);

    // Save sort order
    std::string sort_order_str;
    for (size_t i = 0; i < sort_order.size(); i++) {
        if (i > 0) {
            sort_order_str += ",";
        }
        sort_order_str += std::to_string(std::to_underlying(sort_order[i]));
    }
    ini->SetValue(Name(), "sort_order", sort_order_str.c_str());
}

void InventorySorting::DrawSettingsInternal()
{
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    const auto cursor_y = ImGui::GetCursorPosY();
    ImGui::TextUnformatted("Sort your inventory by item type.");
    ImGui::TextDisabled("Configure the order in which item types should be sorted.");

    const auto original_pos = ImGui::GetCursorPos();
    ImGui::SetCursorPos({ImGui::GetContentRegionAvail().x - 200.f, cursor_y});

    if (ImGui::Button("Sort Inventory!", ImVec2(200.f, 0))) {
        SortInventoryByType();
    }
    ImGui::SetCursorPos(original_pos);
    ImGui::BeginChild("sort_order_list", ImVec2(0, 350), true);

    for (size_t i = 0; i < sort_order.size(); i++) {
        ImGui::PushID(static_cast<int>(i));

        const char* type_name = GetItemTypeName(sort_order[i]);

        // Up arrow button
        if (i > 0) {
            if (ImGui::Button(ICON_FA_ARROW_UP)) {
                std::swap(sort_order[i], sort_order[i - 1]);
            }
        }
        else {
            ImGui::BeginDisabled();
            ImGui::Button(ICON_FA_ARROW_UP);
            ImGui::EndDisabled();
        }

        ImGui::SameLine();

        // Down arrow button
        if (i < sort_order.size() - 1) {
            if (ImGui::Button(ICON_FA_ARROW_DOWN)) {
                std::swap(sort_order[i], sort_order[i + 1]);
            }
        }
        else {
            ImGui::BeginDisabled();
            ImGui::Button(ICON_FA_ARROW_DOWN);
            ImGui::EndDisabled();
        }

        ImGui::SameLine();
        ImGui::Text("%2zu. %s", i + 1, type_name);

        ImGui::PopID();
    }

    ImGui::EndChild();

    ImGui::Spacing();

    if (ImGui::Button("Reset Sort Order", ImVec2(200, 0))) {
        ResetSortOrder();
    }
    ImGui::ShowHelp("Reset to the default sort order.");
}

void InventorySorting::CancelSort()
{
    is_sorting = false;
    show_sort_popup = false;
    pending_cancel = false;
    items_sorted_count = 0;
}
void InventorySorting::RegisterSettingsContent()
{

    ToolboxModule::RegisterSettingsContent(
        "Inventory Settings", ICON_FA_BOXES,
        [this](const std::string&, const bool is_showing) {
            if (is_showing) {
                DrawSettingsInternal();
            }
        },
        1.2f
    );
}

void InventorySorting::SortInventoryByType()
{
    if (is_sorting) {
        Log::Warning("Inventory sort already in progress");
        return;
    }

    if (!IsMapReady()) {
        Log::Warning("Cannot sort inventory while map is loading");
        return;
    }

    // Show popup and set flags
    show_sort_popup = true;
    is_sorting = true;
    items_sorted_count = 0;
    pending_cancel = false;

    Log::Info("Starting inventory sort...");

    // Start the sorting process on a worker thread
    Resources::EnqueueWorkerTask([]() {
        // Structure to hold item information (only data needed for sorting)
        struct ItemInfo {
            uint32_t item_id = 0;
            GW::Constants::Bag bag_id = GW::Constants::Bag::None;
            uint32_t slot = 0;
            int sort_priority = 9999;
            uint32_t model_id = 0;
            GW::Constants::ItemType type;
            ItemInfo(GW::Item* item)
            {
                item_id = item->item_id;
                bag_id = bag_id;
                slot = static_cast<uint32_t>(item->slot);
                type = item->type;
                model_id = item->model_id;
                sort_priority = GetItemTypeSortPriority(type);
            }
            GW::Item* item() { return GW::Items::GetItemById(item_id); }
        };

        std::vector<ItemInfo> items_to_sort;
        std::vector<size_t> bag_sizes(std::to_underlying(GW::Constants::Bag::Max), 0); // Slots available in each bag

        // ====== PHASE 1: Collect all items from inventory bags ======
        bool task_done = false;
        GW::GameThread::Enqueue([&items_to_sort, &bag_sizes, &task_done]() {
            for (auto bag_id = GW::Constants::Bag::Storage_1; bag_id <= GW::Constants::Bag::Storage_14; bag_id = static_cast<GW::Constants::Bag>(std::to_underlying(bag_id) + 1)) {
                GW::Bag* bag = GW::Items::GetBag(bag_id);
                if (!bag || !bag->items.valid()) {
                    continue;
                }

                // Store bag size
                bag_sizes[std::to_underlying(bag_id)] = bag->items.size();

                // Collect items from this bag
                for (auto item : bag->items) {
                    if (!item) continue;
                    items_to_sort.push_back(item);
                }
            }
            task_done = true;
        });

        WAIT_FOR_GAME_THREAD_TASK(task_done, 3000, "Sorting failed to collect inventory item info");

        // ====== PHASE 2: Sort items by priority (in-memory) ======
        std::sort(items_to_sort.begin(), items_to_sort.end(), [](const ItemInfo& a, const ItemInfo& b) {
            // Primary sort: by type priority
            if (a.sort_priority != b.sort_priority) {
                return a.sort_priority < b.sort_priority;
            }

            // Secondary sort: by model ID for consistency
            return a.model_id < b.model_id;
        });

        if (pending_cancel) {
            Log::Info("Sorting cancelled");
            is_sorting = false;
            show_sort_popup = false;
            return;
        }

        // ====== PHASE 3: Move items to sorted positions ======
        for (size_t target_idx = 0; target_idx < items_to_sort.size() && !pending_cancel; target_idx++) {
            const ItemInfo& target_item = items_to_sort[target_idx];

            // Calculate target bag and slot from linear index
            size_t running_slot = target_idx;
            GW::Constants::Bag target_bag = GW::Constants::Bag::None;
            uint32_t target_slot = 0;
            for (auto check_bag = GW::Constants::Bag::Storage_1; check_bag <= GW::Constants::Bag::Storage_14; check_bag = static_cast<GW::Constants::Bag>(std::to_underlying(check_bag) + 1)) {
                const size_t bag_size = bag_sizes[std::to_underlying(check_bag)];
                if (bag_size == 0) {
                    continue;
                }

                if (running_slot < bag_size) {
                    target_bag = check_bag;
                    target_slot = static_cast<uint32_t>(running_slot);
                    break;
                }
                running_slot -= bag_size;
            }

            if (target_bag == GW::Constants::Bag::None) {
                continue; // No valid target position
            }

            // Check if item is already in the correct position
            bool already_in_position = false;
            task_done = false;
            GW::GameThread::Enqueue([&already_in_position, &task_done, target_item, target_bag, target_slot]() {
                GW::Item* item = GW::Items::GetItemById(target_item.item_id);
                if (item && item->bag && item->bag->bag_id() == target_bag && item->slot == target_slot) {
                    already_in_position = true;
                }
                task_done = true;
            });

            WAIT_FOR_GAME_THREAD_TASK(task_done, 3000, "Sorting failed to check item position");

            if (already_in_position) continue;

            // Initiate the move
            task_done = false;
            GW::GameThread::Enqueue([&task_done, target_item, target_bag, target_slot]() {
                GW::Item* item = GW::Items::GetItemById(target_item.item_id);
                if (item) {
                    GW::Items::MoveItem(item, target_bag, target_slot);
                }
                task_done = true;
            });

            WAIT_FOR_GAME_THREAD_TASK(task_done, 3000, "Sorting failed to issue move command");

            // Wait for move to complete (check every 20ms for up to 3 seconds)
            const uint32_t timeout_ms = 3000;

            for (size_t j = 0; j < timeout_ms && !pending_cancel; j += 20) {
                // Check if item has moved to target position
                task_done = false;
                GW::GameThread::Enqueue([&already_in_position, &task_done, target_item, target_bag, target_slot]() {
                    GW::Item* item = GW::Items::GetItemById(target_item.item_id);
                    if (item && item->bag && item->bag->bag_id() == target_bag && item->slot == target_slot) {
                        already_in_position = true;
                    }
                    task_done = true;
                });

                WAIT_FOR_GAME_THREAD_TASK(task_done, 3000, "Sorting failed to verify item move");

                if (already_in_position) {
                    items_sorted_count++;
                    break;
                }

                Sleep(20);
            }
            if (pending_cancel) {
                Log::Info("Sorting cancelled");
                is_sorting = false;
                show_sort_popup = false;
                return;
            }
            // Check for timeout
            if (!already_in_position) {
                Log::Warning("Sorting failed to move item %u to bag %d slot %u", target_item.item_id, std::to_underlying(target_bag), target_slot);
                is_sorting = false;
                show_sort_popup = false;
                return;
            }
        }

        // ====== PHASE 4: Completion ======
        Log::Warning("Inventory sorting complete! %zu items sorted.", items_sorted_count);
        is_sorting = false;
        show_sort_popup = false;
    });
}
