#include <ansi.h>
inherit SUPER_NPC;

string ask_mieyao();
string ask_cancel();

void create()
{
        set_name("常纪", ({ "chang ji", "chang" }));
        set("long", "蜀山常字辈弟子，经常在长安道观处理门下琐事。\n");
        set_weight(1000000);
        set("gender", "男性");
        set("age", 40);
        set_level(90);
        set("attitude", "peaceful");
        set("class","taoist");
        
        set("force_factor", 160);
        set("mana_factor", 250);

        set_skill("spells",900);
        set_skill("force", 900);
        set_skill("dodge", 900);
        set_skill("parry", 900);
        set_skill("sword", 900);
        set_skill("xianfeng-yunti", 900);
        set_skill("zuixian-wangyue", 900);
        set_skill("chuanyun-zhang", 900);
        set_skill("literate", 900);
        set_skill("unarmed", 900);
	set_skill("yujianshu", 900);
        set_skill("tianshi-fufa",900);
        map_skill("spells", "tianshi-fufa");
        map_skill("dodge", "zuixian-wangyue");
        map_skill("force", "xianfeng-yunti");
        map_skill("parry", "yujianshu");
        map_skill("sword", "yujianshu");
        map_skill("unarmed", "chuanyun-zhang");
        set_skill("jiefeng",900);
	set_skill("jianshu",900);
	set_skill("zhili",900);
	
        create_family("蜀山派", 4, "四代弟子");
        set("env/wimpy",10);
	set("env/test","HIR");
	set_temp("weapon_level",40+random(40));
	set_temp("armor_level",40+random(40));    
        
        set("inquiry",([
	   	"kill": (: ask_mieyao :),
	   	"师门任务": (: ask_mieyao :),
	    	"cancel": (: ask_cancel :),        	
        ]));	
        setup();
        carry_object(0,"pifeng",random(2))->wear();
        carry_object(0,"shoes",random(2))->wear();
        carry_object(0,"kui",random(2))->wear();
        carry_object(0,"sword",random(3))->wield();
        carry_object(0,"cloth",random(2))->wear();
        carry_object(0,"armor",random(2))->wear();
}
string ask_mieyao()
{
    	object who=this_player();
    	if((string)who->query("family/family_name")=="蜀山派") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("非我门人,何故来此?\n");
}

string ask_cancel()
{
	if( this_player()->query("family/family_name")!="蜀山派" )
		return 0;
	return "/quest/family/mieyao"->cancel_me(this_player());	
}

void init()
{
	if( this_player()->query("family/family_name")=="蜀山派" 
	 || wizardp(this_player()) )
	{
		add_action("do_list","list");
		add_action("do_buy","buy");
	}
}

int do_list()
{
	write(@LONG
你可以购买下列这些东西：
千叠桃符纸(seal)                  ：十两白银
LONG);
	return 1;
}

int do_buy(string arg)
{
	string id;
	object seal,me = this_player();
	if( !arg || sscanf(arg,"seal from %s",id)!=1 )
		return 0;
	if( !id(id) )
		return 0;
	if( !me->check_pay(1000) )
		return err_msg("你身上的钱不足"+MONEY_D->money_str(1000)+"。\n");		
	seal = new("/obj/paper_seal");
	seal->set_amount(1000);	
	seal->set("no_give",1);
	seal->set("value",0);
	seal->set_weight(100);
	seal->set("no_put",1);
	seal->set("no_get",1);
	if( seal->move(me) )
	{
		me->money_add(-1000);
		me->save(1);
		return err_msg("你向常纪买下一些桃符纸。\n");
	}
	else
	{
		if( seal ) destruct(seal);
		return err_msg(HIR"【系统】你身上的背包满了。"NOR"\n");
	}
}

string short()
{
	string str = ::short();
	str+= NOR YEL" ㊣"NOR;
	return str;
}

void die()
{
	powerup(0,1);
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
}

void unconcious() 
{
	die();
}

void kill_ob(object who)
{
	EMOTE_D->do_emote(this_object(), ({"shake","pei","zeze"})[random(3)],geteuid(who),CYN,0,0,0);
	all_inventory(environment())->remove_killer(this_object());
	this_object()->remove_all_killer();
}	
