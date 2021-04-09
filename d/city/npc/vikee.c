#include <ansi.h>
inherit NPC;

mixed random_msg()
{
	string msg;
	object *inv;
	int i,f=0;
	
	if( !environment() ) 
		return;
	inv = all_inventory(environment());
	if( !inv || sizeof(inv)<2 )
		return;
	for(i=0;i<sizeof(inv);i++)	
	{
		if( userp(inv[i]) )
		{
			f++;
			break;
		}
	}
	if( f==0 )
		return;
	msg = ({
		"小雨轻声告诉你：新手可以问我要新手启东资金哦，输入yao gold就行了。\n",
        	"小雨悄悄的对你说：我这有上好的松鹤龟苓膏，想要吗？\n",	
        })[random(2)];
        tell_room(environment(),msg);
        return 1;
}

void create()
{
	set_name(HIG"小雨"NOR"", ({"xiao rain","rain","zong guan"}));
	set("long", "
    他是发送装备的总管小雨。
    你可以用yao 来要装备或道具(比如yao sword)：
──────────────────────────────
盔甲：
          甲(armor)        靴(shoes)     盾(shield)
          盔(kui)          衣(cloth)     披风(pifeng)
兵器：
          棒(stick)        剑(sword)     筋(whip)
          刀(blade)        爪(zhua)      杖(staff)
          斧(axe)          铲(fork)      锤(hammer)
          枪(spear)        琴(qin)       锏(mace)
          匕首(dagger)
特殊:
          天师法冠(bonnet)    松鹤龟苓膏(gao)
──────────────────────────────
\n");
	set("gender", "男性");
	set("age", 1);
	set("per", 40);
	set("combat_exp",60000000);
	set_skill("unarmed",800);
	set_skill("changquan",800);
	set("title",""HIG"装备总管");
	set_skill("literate", 800);
	set("chat_chance",10);
        set("chat_msg", ({
        	(: random_msg :),
        }));
	setup();
	carry_object("/d/obj/cloth/magua")->wear();
}

void init()
{
	::init();
  	add_action("do_cmds", ({"fight","kill","steal","cast","ji","throw",}));
  	add_action("do_list","list");
  	add_action("do_yao","yao");
}

void die()
{
	powerup(0,1);
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
 	return;
}

int do_cmds(string arg)
{
	return err_msg("小雨朝你摇了摇头。\n");
}

void kill_ob(object who)
{
	message_vision("$N朝$n摇了摇头。\n",this_object(),who);
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
}

int do_yao(string arg)
{
	mixed local;
	int week;
	string type;
	object ob;
	object who=this_player();
	object me=this_object();

	if( !arg)
		return notify_fail("你想要什么？兵器？还是盔甲？(比如:yao sword)\n");

	ob = 0;
	sscanf(arg,"%s",type);
	switch(type)
	{
		//盔甲
		case "armor" : ob=new("/d/city/npc/obj/armor.c");break;
		case "pifeng": ob=new("/d/city/npc/obj/pifeng.c");break;
		case "shield": ob=new("/d/city/npc/obj/shield.c");break;
		case "shoes" : ob=new("/d/city/npc/obj/shoes.c");break;
		case "cloth" : ob=new("/d/city/npc/obj/cloth.c");break;
		case "kui"   : ob=new("/d/city/npc/obj/kui.c");break;
		//兵器
		case "sword" : ob=new("/d/city/npc/obj/sword.c");break;
		case "whip"  : ob=new("/d/city/npc/obj/whip.c");break;
		case "blade" : ob=new("/d/city/npc/obj/blade.c");break;
		case "dagger": ob=new("/d/city/npc/obj/dagger.c");break;
		case "stick" : ob=new("/d/city/npc/obj/stick.c");break;
		case "spear" : ob=new("/d/city/npc/obj/spear.c");break;
		case "fork"  : ob=new("/d/city/npc/obj/fork.c");break;
		case "hammer": ob=new("/d/city/npc/obj/hammer.c");break;
		case "qin"   : ob=new("/d/city/npc/obj/qin.c");break;
		case "axe"   : ob=new("/d/city/npc/obj/axe.c");break;
		case "staff" : ob=new("/d/city/npc/obj/staff.c");break;
		case "zhua"  : ob=new("/d/city/npc/obj/zhua.c");break;           
		case "bonnet": ob=new("/d/city/npc/obj/bonnet.c");break;           
		case "mace"  : ob=new("/d/city/npc/obj/mace.c");break;     
		case "gao"   : 
			local = localtime(time());      
			week = local[6];
			if( who->query("mark/last_gingive")==week )
				return err_msg(CYN"小雨说道：你今天已经领过了。\n"NOR);
			if( who->query("gin")>=10 )
				return err_msg(CYN"小雨说道：你现在活力充沛，还不需要吃松鹤龟苓膏。\n"NOR);
			EMOTE_D->do_emote(this_object(), "ok",geteuid(who),CYN,0,0,0);
			who->set("gin",who->query_maxgin());
			message_vision(HIG"$N"HIG"吃下一粒小雨递过来的"HIY"松鹤龟苓膏"HIG"，顿时感到活力充沛。\n"NOR,who);
                        who->add("mark/"+week+"_gingived",1);
                        log_file("gin",XYJTIME_D->chinese_time(time())+" "+who->query("id")+" get 1/"+who->query("mark/"+week+"_gingived")+" gao frin xiao rain\n");
			if( who->query("mark/"+week+"_gingived")>=3 )
			{
				who->set("mark/last_gingive",week);
				who->delete("mark/"+week+"_gingived");
				tell_object(who,HIR"【系统】你今日已领完"HIY"三"HIR"次"HIW"松鹤龟苓膏"HIR"。"NOR"\n");
			}
			return 1;
		case "gold" :
			if( who->query_level()>=20 && !wizardp(who) )
				return err_msg("小雨鄙夷的看着你。\n");
			if( (who->check_balance(1000000)|| who->check_pay(1000000))
			 && !wizardp(who) )
				return err_msg("你感觉你自己不差钱。\n");
			if( who->query("mark/newbie_gold") )
				return err_msg("你为自己吃喝等死的态度感到非常羞愧。\n");	
                        who->money_add(1000000);
			who->set("mark/newbie_gold",1);
			who->save(1);
			message_vision("小雨递给$N一百两"HIY"黄金"NOR"。\n",who);
			log_file("newbie",XYJTIME_D->chinese_time(time())+" "+who->query("id")+" 得到了新手启东资金。\n");
			return 1;
		default : 	
		      	return err_msg(@LONG
    你可以用yao 来要装备或道具(比如yao sword)：
──────────────────────────────
盔甲：
          甲(armor)        靴(shoes)     盾(shield)
          盔(kui)          衣(cloth)     披风(pifeng)
兵器：
          棒(stick)        剑(sword)     筋(whip)
          刀(blade)        爪(zhua)      杖(staff)
          斧(axe)          铲(fork)      锤(hammer)
          枪(spear)        琴(qin)       锏(mace)
          匕首(dagger)
特殊:
          天师法冠(bonnet)    松鹤龟苓膏(gao)
──────────────────────────────
LONG);
	}
	if( ob )
	{
		ob->set("no_sell", 1);
        	ob->set("no_get", 0);
		ob->set("no_drop", 1);
        	ob->set("no_give", 1);
        	ob->set("from","新手准备室");
        	if( ob->move(who) )
			tell_object(who,"小雨把"+ob->query("name")+"交给你,并告诉你:带好，别乱丢哦！\n");
		else
		{
			if( ob ) destruct(ob);
			tell_object(who,"小雨说：你背包满了吧。\n");
		}
	}
	return 1;
}
