/**
	Grid
	Shows a simple grid menu.
*/

#include MenuStyle_List

local Name = "Grid Menu";

func Construction()
{
	inherited(...);
	this.Style = GUI_GridLayout;
}

// custom_menu_id should be passed if the menu was manually opened and not via Open()
func AddItem(symbol, string text, user_ID, proplist target, command, parameter, custom_entry, custom_menu_id)
{
	custom_menu_id = custom_menu_id ?? menu_id;
	
	var on_hover = GuiAction_SetTag("OnHover", 0, nil);
	if (on_mouse_over_callback)
		on_hover = [on_hover, GuiAction_Call(this, "DoCallback", on_mouse_over_callback)];
	var on_hover_stop = GuiAction_SetTag("Std", 0, nil);
	if (on_mouse_out_callback)
		on_hover_stop = [on_hover_stop, GuiAction_Call(this, "DoCallback", on_mouse_out_callback)];
	
	var ID = GetLength(entries) + 1;
	if (!custom_entry)
	{
		custom_entry = {Bottom = "+4em", Right = "+4em", desc = {Top = "100%-1em"}};
		custom_entry.Symbol = symbol;
		custom_entry.desc.Text = text;
		custom_entry.desc.Style = GUI_TextRight;
		custom_entry.ID = ID;
		custom_entry.Target = this;
		custom_entry.Priority = ID;
		custom_entry.BackgroundColor = {Std = 0, OnHover = 0x50ff0000};
		custom_entry.OnClick = GuiAction_Call(this, "OnClick");
		custom_entry.OnMouseIn = on_hover;
		custom_entry.OnMouseOut = on_hover_stop;
	}
	entries[ID - 1] = [target, command, parameter, user_ID];
	this[Format("menuChild%d", ID)] = custom_entry;
	
	// need to add to existing menu?
	if (custom_menu_id)
	{
		var temp = {child = custom_entry};
		CustomGuiUpdate(temp, custom_menu_id, this.ID, this);
	}
	
	return custom_entry;
}