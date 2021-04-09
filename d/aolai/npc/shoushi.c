#include <ansi.h>
inherit NPC;

nosave string goods_msg="";
nosave mapping goods_list = ([]);
nosave mapping temp_list = ([]);
void init_shop_goods();

void create()
{
        set_name("家文", ({"jia wen", "wen","boss"}));
        set("title", "首饰店老板");
        set_level(15);
        set("gender", "男性");
        set("age", 25);
        set("long", "首饰店老板。人长很清秀，所以店里生意简直是好到爆。\n");
	set_skill("snowsword", 130);
        set_skill("sword", 150);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
	set_skill("moondance", 150);
	map_skill("dodge", "moondance");
	map_skill("sword", "snowsword");
	map_skill("parry", "snowsword");
	set("force_factor", 5);
        set("env/test","HIM");
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"hand",1)->wear();
        carry_object(0,"unarmed",1)->wield();
        init_shop_goods();
}

void init()
{
        ::init();
        add_action("do_list", "list");
}

void init_shop_goods()
{
	int i,k,level,base_value = 500;
	object ob;
	string *files = ({
		"ring","neck","hand","waist","wrists",
	});
	level = 5;
	for(k=1;k<level;k++)
	{
		reset_eval_cost();
		for(i=0;i<sizeof(files);i++)
		{
			ob = new(sprintf("/d/obj/narmor/%s",files[i]));
			if( !ob )
				continue;
			if( !ob->init_armor(k) )
				continue;
			if( !undefinedp(temp_list[ob->short()]) )
				continue;	
			if( !temp_list || !mapp(temp_list) )
				temp_list = ([ ob->short() : files[i]+" "+k ]);
			else	temp_list[ob->short()] = files[i]+" "+k;	
			if( !goods_list || !mapp(goods_list) )
				goods_list = ([ files[i]+" "+k : ({files[i],k*base_value}),]);
			else	goods_list[files[i]+" "+k] = ({files[i],k*base_value});		
			goods_msg+= sprintf("%30-s  %4-s  %15-s\n",ob->name()+"("+files[i]+" "+k+")",ob->query("level")+"",MONEY_D->money_str(k*base_value,1),);
			if( ob )
				destruct(ob);
		}
	}		
}

int do_list()
{
	string str;
	object me = this_player();
	printf("你可以购买下列这些东西：\n");
	printf(REV CYN"       名称                 等级要求    价格\n"NOR);
	me->start_more(goods_msg); 
	return 1;
}

int accept_fight(object me)
{
        command("say 哼，劳资地盘上也敢撒野！\n");
        return 1;
}

int buy_object(object who,string str)
{
	string arg;
	object ob;
	int value,v;
	if( !goods_list || !mapp(goods_list) )
	{
		tell_object(who,"现在暂无商品可卖。\n");
		return -1;
	}
	if( undefinedp(goods_list[str]) )
	{
		tell_object(who,"没有此首饰可买，请看清ID，比如 buy armor 1 from luo\n");
		return -1;
	}
	sscanf(str,"%s%d",arg,v);
	if( v<1 )
	{
		tell_object(who,"首饰等级初始出错，请联系巫师。\n");
		return -1;
	}
	arg = goods_list[str][0];
	value = goods_list[str][1];
	if( value<=0 )
	{
		tell_object(who,"首饰价格初始出错，请联系巫师。\n");
		return -1;
	}
	if( !who->check_pay(value) )
	{
		tell_object(who,"你身上的钱不足"+MONEY_D->money_str(value,1)+"。\n");
		return -1;
	}
	ob = new("/d/obj/narmor/"+arg);
	if( !ob )
	{
		tell_object(who,"首饰初始出错，请联系巫师。\n");
		return -1;
	}
	if( !ob->init_armor(v) )
	{
		if( ob )  destruct(ob);
		tell_object(who,"首饰初始出错，请联系巫师。\n");
		return -1;
	}
	if( !ob->move(who) )
	{
		if( ob )  destruct(ob);
		tell_object(who,"你的背包满了。\n");
		return -1;
	}
	if( !who->money_add(-value) )
	{
		if( ob )  destruct(ob);
		tell_object(who,"购买失败，请联系巫师。\n");
		return -1;
	}
	tell_object(who,HIY"你购买了一"+ob->query("unit")+ob->short()+HIY"。\n"NOR);				 
	ob->set("value",1);	
	return -1;
}