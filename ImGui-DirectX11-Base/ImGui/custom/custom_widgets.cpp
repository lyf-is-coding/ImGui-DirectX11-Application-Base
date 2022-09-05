#include "custom_widgets.h"

bool ImGui::ImageButton(ImTextureID texture_id, ImVec2 texture_size, const char* text, const char* text_end, const int text_lines, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1)
{
    // Setup
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = GetCurrentWindow();
    ImGuiStyle& style = GetStyle();

    if (window->SkipItems) return false;
    
    // Register item
    std::string id_str(text); id_str += text_end;
    const ImGuiID id = window->GetID(id_str.c_str());
    const ImVec2 padding = g.Style.FramePadding;

    ImRect bb(window->DC.CursorPos, window->DC.CursorPos + texture_size);
    bb.Max.x += padding.x * 4;
    bb.Max.y += text_lines * GetTextLineHeight() + padding.y * 2;

    ItemSize(bb);
    if (!ItemAdd(bb, id)) return false;

    // Interaction
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    // Render background
    const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    RenderFrame(bb.Min, bb.Max, col, true, 6.0f);

    // Render image
    const ImVec2 image_pos_min(bb.GetCenter().x - texture_size.x / 2, bb.Min.y + padding.y);
    const ImVec2 image_pos_max = image_pos_min + texture_size;
    window->DrawList->AddImage(texture_id, image_pos_min, image_pos_max, uv0, uv1);

    // Render text
    const ImVec2 text_pos(bb.GetCenter().x, image_pos_max.y);
    const float rendering_width = bb.GetWidth() - padding.x;

    float space_left = 0;
    std::string line = "";
    bool is_ok_to_render = false;
    int skipped_line = 0;

    std::vector<std::string> parsed_words = Utils::parse_str(std::string(text), ' ');

    for (int word_index = 0; word_index < parsed_words.size(); ++word_index)
    {
        ImVec2 word_size = CalcTextSize(parsed_words[word_index].c_str());

        // Use space left from the last word wrap.
        if (space_left)
            space_left -= word_size.x;
        // New line.
        else
            space_left = rendering_width - word_size.x;

        if (space_left == 0)
        {
            line += parsed_words[word_index];

            is_ok_to_render = true;
        }
        else if (space_left > 0)
        {
            line += parsed_words[word_index];

            int next_word_index = word_index + 1;

            // If there is still word for concating
            if (next_word_index != (int)parsed_words.size())
            {
                // If there is still space for next word
                if (space_left - CalcTextSize(parsed_words[next_word_index].c_str()).x - CalcTextSize(" ").x >= 0)
                    line += ' ';
                else
                    is_ok_to_render = true;
            }
        }
        // The current word size exceeds rendering width.
        // We need to find a shorter version of it that fits the rendering width.
        else
        {
            std::string suitable_word = "";
            
            // Remove the last character one by one until we find a suitable word.
            for (int char_index = (int)parsed_words[word_index].size() - 1; char_index >= 0; --char_index)
            {
                suitable_word = parsed_words[word_index].substr(0, char_index);

                ImVec2 suitable_word_size = CalcTextSize(suitable_word.c_str());

                // Check if the current word fits the rendering width.
                if (rendering_width - suitable_word_size.x >= 0)
                {   
                    // Use the remaining part for next-line rendering.
                    parsed_words.insert(parsed_words.begin() + word_index + 1, parsed_words[word_index].substr(char_index));
                    break;
                }
            }

            is_ok_to_render = true;
            line += suitable_word;
        }

        // Truncate string. All remaining words will be replaced with ...
        if (is_ok_to_render && skipped_line + 1 == text_lines && word_index + 1 < (int)parsed_words.size())
        {
            line += "...";

            ImVec2 render_pos(text_pos.x - CalcTextSize(line.c_str()).x / 2, text_pos.y + skipped_line * GetTextLineHeight());
            window->DrawList->AddText(render_pos, ImColor(255, 255, 255), line.c_str());

            break;
        }

        // Force render if there is no more word for wrapping.
        if (is_ok_to_render || word_index + 1 == (int)parsed_words.size())
        {
            ImVec2 render_pos(text_pos.x - CalcTextSize(line.c_str()).x / 2, text_pos.y + skipped_line * GetTextLineHeight());
            window->DrawList->AddText(render_pos, ImColor(255, 255, 255), line.c_str());

            is_ok_to_render = false;
            line = "";
            ++skipped_line;
            space_left = 0;
        }
    }
    
    return pressed;
}