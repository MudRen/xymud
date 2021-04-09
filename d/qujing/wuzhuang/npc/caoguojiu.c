// caoguojiu.c...weiqi, 98.02.24.
#include <ansi.h>

inherit NPC;
int fly_sea();

void create()
{
	set_name("曹国舅", ({"cao guojiu", "cao", "guojiu"}));
      set_level(59);
	//set("title", "");
	set("gender", "男性" );
	set("age", 40);
	set("per", 20);
	set("long", "一位神情严肃的中年人。曹国舅名景休，天资纯善，\n不喜富贵，酷慕清虚。其弟骄纵不法，后罔逃国宪。\n曹国舅深以为耻，遂隐迹山林，精思元理。后投入镇元门下。\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 200000);

	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 560);
	set_skill("wuxing-quan", 560);
	set_skill("dodge", 580);
	set_skill("baguazhen", 570);
	set_skill("parry", 580);
	set_skill("hammer", 590);
	set_skill("kaishan-chui", 500);
	set_skill("force", 570);   
	set_skill("zhenyuan-force", 570);
	set_skill("literate", 560);
	set_skill("spells", 580);
	set_skill("taiyi", 580);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("hammer", "kaishan-chui");
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
	carry_object(0,"hammer",random(3))->wear();
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
	"清茶",
	"羊奶酒",
	"泡的已经没有味的茶水",
	"清水",
	"白烧酒",
	"西湖龙井茶",
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
      if (me->query("wzggive/caoguojiu"))
    	{
	 		  message_vision(MAG"\n曹国舅问道：我要的"+CYN""+me->query("wzggive/caoguojiu")+MAG"可曾拿到了吗？！\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/caoguojiu")!="give")
	    {
	      jname = jnames[random(sizeof(jnames))];
		  message_vision(MAG"\n曹国舅乐呵呵的打着白玉板说道：好主意，记得带上点"+CYN""+jname+NOR"！\n",me);
		  me->set("wzggive/caoguojiu",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "快去叫上其他八仙，我先走一步了！\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/caoguojiu"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/caoguojiu"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }

  message_vision(MAG"\n$N乐呵呵的捧着$n自言自语道：$n呀，$n，今天你就陪着国舅爷去东海玩玩．\n"NOR,me,ob);
  who->set_temp("wzg/caoguojiu","give");
  who->delete("wzggive/caoguojiu");
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