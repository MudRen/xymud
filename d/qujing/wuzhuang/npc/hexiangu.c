// hexiangu.c...weiqi, 98.02.24.
#include <ansi.h>
int fly_sea();
inherit NPC;
void create()
{
	set_name("何仙姑", ({"he xiangu", "he", "xiangu"}));
      set_level(40);
	//set("title", "");
	set("gender", "女性" );
	set("age", 25);
	set("per", 20);
	set("long", "何仙姑深得镇元大仙喜爱，各位同门大多跟她交好。\n何仙姑原名何秀姑，父亲是开豆腐坊的，她投入五庄观前是当地有名的“豆腐西施”。\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 200000);

	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 660);
	set_skill("wuxing-quan", 660);
	set_skill("dodge", 680);
	set_skill("baguazhen", 680);
	set_skill("parry", 680);
	set_skill("sword", 690);
	set_skill("sanqing-jian", 700);
	set_skill("force", 700);   
	set_skill("zhenyuan-force", 700);
	set_skill("literate", 650);
	set_skill("spells", 680);
	set_skill("taiyi", 680);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("sword", "sanqing-jian");
	map_skill("dodge", "baguazhen");

	set("max_kee", 500);
	set("max_sen", 500);
	set("force", 1000);
	set("max_force", 800);
	set("mana", 1600);
	set("max_mana", 800);	
	set("force_factor", 40);
	set("mana_factor", 40);
    set("inquiry",([
    //"重游东海": (: fly_sea :),
		]));
	setup();
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"shoes",random(3))->wear();
	carry_object(0,"neck",random(3))->wear();
	carry_object(0,"ring",random(3))->wear();
	carry_object(0,"sword",random(3))->wield();
}

int fly_sea()
{
  string *jnames = ({
    "酥合香油",
	"羊奶酒",
	"桂花酒",
	"云雾山香茶",
	"碧樨茶",
	"玄火酒",
	"西湖龙井茶",
	});  
   	string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/hexiangu"))
    	{
	 		  message_vision(HIM"\n何仙姑问道：那"+CYN""+me->query("wzggive/hexiangu")+HIM"可曾拿到了吗？！\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/hexiangu")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(HIM"\n何仙姑欠身施礼道：如" + RANK_D->query_respect(me) + "能带上"+CYN""+jname+HIM"那秀姑也同去！\n"NOR,me);
		  me->set("wzggive/hexiangu",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "快去叫上其他八仙，说秀姑在东海边等他们！\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/hexiangu"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/hexiangu"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }

  message_vision(HIM"\n$N接过$n连声称赞道：早就想尝尝这"+who->query("wzggive/hexiangu")+"了．\n"NOR,me,ob);
  who->set_temp("wzg/hexiangu","give");
  who->delete("wzggive/hexiangu");
  return 1;
}



void return_ob (object who, object ob)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}

void attempt_apprentice(object ob)
{
	EMOTE_D->do_emote(this_object(), "ok",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们道家发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","万寿山五庄观又多了一个弟子  "+ob->name(1)+HIW"\n                                 五庄观的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "xian");
}