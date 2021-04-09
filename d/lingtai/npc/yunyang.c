// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
//puti.c
inherit SUPER_NPC;
inherit F_MASTER;
#include <ansi.h>
#include "/d/lingtai/npc/zhenfa.h"

string begin_go();
string expell_me(object me);
string ask_mieyao();
string ask_cancel();

void create()
{
	set_name("云阳真人", ({"master yunyang", "master", "yunyang"}));
	set_level(130);
    	set("long", "云阳真人与菩提祖师实是半师半友，也是三星洞内外总管．
因其壮年时降魔除妖无数，人称「小天师」。\n");
	set("faith",4000);
	set("gender", "男性");
   	set("title", "小天师");
   	set("class", "taoist");
       	set("age", 70);
       	set("attitude", "friendly");
       	set("shen_type", 1);
       	set("rank_info/respect", "老道长");
	set("force_factor", 380);
       	set("mana_factor", 460);

     	set("eff_dx", 250000);
     	set("nkgain", 400);

       	set_skill("literate", 1300);
	set_skill("unarmed",1300);
    	set_skill("dodge",1300);
    	set_skill("parry",1300);
	set_skill("stick",1300);
	set_skill("spells",1300);
	set_skill("dao",1300);
	set_skill("puti-zhi",1300);
	set_skill("wuxiangforce",1300);
	set_skill("force",1300);
	set_skill("qianjun-bang",1300);
	set_skill("jindouyun",1300);
   	map_skill("spells", "dao");
   	map_skill("unarmed", "puti-zhi");
   	map_skill("force", "wuxiangforce");
   	map_skill("stick", "qianjun-bang");
   	map_skill("parry", "qianjun-bang");
   	map_skill("dodge", "jindouyun");
     	set("inquiry", ([
		"灭妖": (: ask_mieyao :),
		"kill": (: ask_mieyao :),
     		"下山": (: expell_me :),
    		"灵台观礼": (: begin_go :),
     		"leave": (: expell_me :),
     		"cancel": (: ask_cancel :),
     		"四象阵" : (: ask_sixiang :),
     		"八卦阵" : (: ask_bagua :),
	]) );
	create_family("方寸山三星洞", 2, "蓝");
	set_temp("weapon_level",60);
	set_temp("armor_level",60);
	set("env/test","HIR");
	setup();
        carry_object(0,"stick",1)->wield();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"ring",1)->wear();
}

string ask_cancel()
{
	mixed foo = this_player()->cancel_job("师门任务");
	if( !foo || !stringp(foo) || this_player()->query("family/family_name")!="方寸山三星洞" )
		return 0;
	if( this_player()->query("faith")<10 )
		return "你师门贡献不足也。";
	this_player()->add("faith",-10);
	tell_object(this_player(),HIY"【师门】你失去了10点师门贡献。\n"NOR);
	this_player()->save();	
	return foo;	
}

string expell_me(object me)
{       
	me=this_player();
      	if((string)me->query("family/family_name")=="方寸山三星洞") 
      	{
  		if( me->query_level()<40 )
     			return ("这么早就离开,你是来偷我方寸的绝技的吧.");
		else
             	{
                	me->set_temp("betray", "fc");
                	return ("你既是执意下山，为师却有几句话说。\n我方寸山也是名门正派，道家正宗。国有国法，山有山规！\n既是要出山，却需受山规惩罚，你可愿意(agree)?");
       		}
       	}
        return ("贫道不知。");
}

void init()
{
	::init();
      	add_action("do_agree", "agree");
}

int do_agree(string arg)
{
	if((string)this_player()->query("family/family_name")!="方寸山三星洞")
		return 0;
        if(this_player()->query_temp("betray")=="fc") 
        {
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{        	
                	message_vision("$N答道：弟子愿意。\n\n", this_player());
                	command("say 既是我方寸山池浅容不下蛟龙，你便下山去吧！");
			command("say 江湖风波，善恶无形，好自为之。。。\n");
                	return 1;
                }
	}                
        return 0;
}

string ask_mieyao()
{
    	object who=this_player();

    	if((string)who->query("family/family_name")=="方寸山三星洞") 
    	{
      		EMOTE_D->do_emote(this_object(), ({"addoil","touch","ok"})[random(3)],geteuid(who),CYN,0,0,0);
      		return "/quest/family/mieyao"->query_yao(who);
    	}
    	return ("贫道不知。");
}

string begin_go()
{
	string str,*msgs;
	int i,k;
	object me = this_player();
	mapping GuanLi = ([
		"moon"	: "月宫祖师西王母",
		"hell"  : "地府祖师地藏菩萨",
  		"jjf"   : "将军府祖师白发老人",
  		"pansi" : "盘丝洞祖师金灵圣母",
  		"bhg"   : "百花谷现任掌门凝眸仙子",
		"shushan" : "蜀山剑派现任掌门剑圣",
		"wzg"	: "五庄观地仙之祖镇元大仙",
		"sea"   : "东海水晶宫敖广龙王爷",
		"putuo" : "南海普陀山观世音菩萨",
	]);	
	if( me->query("family/family_name")!="方寸山三星洞"
	 || me->query("class")!="taoist" )
		return 0;
	if( me->is_knowing("puti_panlong") )
       		return RANK_D->query_respect(me) + "善有善报，恶有恶报，凡事要三思而后行啊！";
       	if( me->query_temp("pendding/fc_visite") )
       	{
       		str = "";
       		msgs = keys(GuanLi);
       		k = 0;
       		for(i=0;i<sizeof(msgs);i++)
       		{
       			if( me->query_temp("pendding/fc_visite_"+msgs[i]) )
       			{
       				str+= GuanLi[msgs[i]];
       				k++;
       				if( k<me->query_temp("pendding/fc_visited") )
       					str+= "、";
       			}
       		}
       		if( k==0 )
       			return "你还不即可动身？";
       		me->set_temp("pendding/fc_visited",k);
		str = "干得不错。\n云阳真人说道：到如今你已请得"+str+"等"+chinese_number(k)+"位圣贤前来观礼。";
		str = sort_msg(str);
		return str;				
       	}
	EMOTE_D->do_emote(this_object(), "nod",geteuid(me),CYN,0,0,0);
	me->set_temp("pendding/fc_visite",1);
      	return "难得"+me->name()+RANK_D->query_respect(me) + "如此热心，那就有劳代我方寸山弟子前去邀请各派仙家同道同赴灵台观礼。";
}

void attempt_apprentice(object ob)
{
	tell_object(ob,CYN+name()+CYN"说道：某天劫在即，无心授徒尔。\n"NOR);
}	