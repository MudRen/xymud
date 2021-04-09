// tieguaili.c...weiqi, 98.02.24.

#include <ansi.h>
inherit NPC;
int fly_sea();

void create()
{
	set_name("铁拐李", ({"tieguai li", "tieguai", "li"}));
      set_level(40);
	//set("title", "");
	set("gender", "男性" );
	set("age", 42);
	set("per", 12);
	set("long", "他脚登一双烂草鞋，身着一件早就没了本来面目的脏袍，嘴里哼着走调小曲，一副悠闲神态。\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 300000);

	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 660);
	set_skill("wuxing-quan", 660);
	set_skill("dodge", 680);
	set_skill("baguazhen", 680);
	set_skill("parry", 680);
	set_skill("staff", 690);
	set_skill("fumo-zhang", 700);
	set_skill("force", 700);   
	set_skill("zhenyuan-force", 700);
	set_skill("literate", 620);
	set_skill("spells", 680);
	set_skill("taiyi", 680);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("staff", "fumo-zhang");
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
	carry_object("/d/obj/cloth/pobuyi")->wear();
	carry_object("/d/obj/cloth/lancaoxie")->wear();
	carry_object(0,"staff",random(3))->wield();
}

int fly_sea()
{
  string *jnames = ({
    "热酒",
    "清白老酒",
    "水酒",
    "酥合香油",
    "淡茶",
    "江米酒",
    "老白干",
	"米酒",
	"羊奶酒",
	"泡的已经没有味的茶水",
	"清水",
	"白烧酒",
	"西湖龙井茶",
	"清茶",
	"桂花酒",
	"云雾山香茶",
	"碧樨茶",
	"玄火酒",
  });  
   	string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/tieguaili"))
    	{
	 		  message_vision(HIG"\n铁拐李问道：我要的"+CYN""+me->query("wzggive/tieguaili")+HIG"可曾拿到了吗？！\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/tieguaili")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(HIG"\n铁拐李眼睛一亮对$N说道：好，好，好，要是再带上点"+CYN""+jname+HIG"就更好了！\n"NOR,me);
		  me->set("wzggive/tieguaili",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "快去叫上其他八仙，我先走一步了！\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/tieguaili"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/tieguaili"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }
  

  message_vision(HIG"\n$N笑眯眯的捧着$n自言自语道：小$n呀，今天我就带你去东海玩玩．\n"NOR,me,ob);
  who->set_temp("wzg/tieguaili","give");
  who->delete("wzggive/tieguaili");
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