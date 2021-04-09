#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name(HIY"先"HIC"天"HIW"无"HIG"极"HIR"丹"NOR, ({"wuji dan", "wujidan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "粒");
		set("long", "这是一粒贵重的先天无极丹。为巫师奖励给有贡献的玩家。\n");
		set("no_sell",1);
		set("no_get",1);
		set("no_steal",1);
		set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
		set("drug_type", "良药");
	}
	set("is_monitored",1);
	setup();
}

int do_eat(string arg)
{
	if (!id(arg))
		return notify_fail("你要吃什么东西？\n");
		this_player()->add("combat_exp", 20000);
		this_player()->add("daoxing", 20000);
		this_player()->add("potential",10000);
		message_vision(BLU"$N吃下一颗先天无极丹,只觉得自己又变利害了一些 !\n"NOR, this_player());
		log_file("static/jiangli","["+ctime(time())+"] "+sprintf("%s(%s)吃了%O\n",
         this_player()->query("name"),this_player()->query("id"),this_object()));
//    	CHANNEL_D->do_channel(this_player(), "chat", HIG""+this_player()->query("name")+HIM"得到一粒"HIG+name()+HIM"！\n"NOR);
	message("chat",HIM"\n【特别奖励】:"HIG+this_player()->query("name")+HIM"得到一粒"HIG+name()+HIM"的奖励！\n"NOR,users());
		destruct(this_object());
		return 1;
}

