// vendor.c

#include <dbase.h>

int buy_object(object me, string what)
{
	string ob;

	if( stringp(ob = query("vendor_goods/" + what)) )
		return ob->query("value");
	else
		return 0;
}

int complete_trade(object me, string what)
{
	string ob_file;
	object ob;

	if( stringp(ob_file = query("vendor_goods/" + what)) ) {
		ob = new(ob_file);
		if(!ob->move(me)) return 0;
		message_vision("$N向$n买下一" + 
			ob->query("unit") + ob->query("name") + "。\n",
			me, this_object() );
		return 1;
	}
	return notify_fail("没有这样东西卖。\n");
}

string price_string(int v)
{
	if( v%10000 == 0 )
		return (v/10000) + "两黄金";
	if( v%100 == 0 )
		return (v/100) + "两银子";
	return v + "文钱";
}

int do_vendor_list(string arg)
{
	mapping goods;
	string list, *name;
	int i;
	string tlist;

	if( !mapp(goods = query("vendor_goods")) ) return 0;
	if( arg && !this_object()->id(arg) ) return 0;
	name = keys(goods);
	list = "你可以购买下列这些东西：\n";
	for(i=0; i<sizeof(name); i++)  {
		tlist = sprintf("%s(%s)", goods[name[i]]->query("name"), name[i]);
		list += sprintf("%-30s：%s\n", tlist,
			price_string(goods[name[i]]->query("value")) );
        }
	write(list);
	return 1;	
}
