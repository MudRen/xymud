
// ludongbin.c...weiqi, 98.02.24.
#include <ansi.h>
int fly_sea();
string give_book();
string ask_jinguzhou();

inherit NPC;
void create()
{
	set_name("吕洞宾", ({"lu dongbin", "lu", "dongbin"}));
      set_level(70);
	//set("title", "纯阳子");
	set("gender", "男性" );
	set("age", 35);
	set("per", 30);
	set("long", "吕洞宾大概是镇元门下最出名的弟子了，文采风流，色胆包天。\n");
	set("class", "xian");
	set("combat_exp", 120000);
  set("daoxing", 800000);

	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 690);
	set_skill("wuxing-quan", 690);
	set_skill("dodge", 680);
	set_skill("baguazhen", 680);
	set_skill("parry", 680);
	set_skill("sword", 690);
	set_skill("sanqing-jian", 700);
	set_skill("force", 700);   
	set_skill("zhenyuan-force", 700);
	set_skill("literate", 700);
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

	set("inquiry", ([
		"name" : "五庄观纯阳子是也。\n",
		"here" : "身在何处？心老普陀。\n",
   	    "重游东海": (: fly_sea :),
    	"rumors": (: ask_jinguzhou :),
		"心得" : (: give_book :),		 
		"纯阳心得" : (: give_book :),
	]) );

	set("no_book", 0);

	setup();
	carry_object("/d/obj/cloth/xianpao")->wear();
	carry_object("/d/obj/weapon/sword/changjian")->wield();
}
int fly_sea()
{
    string jname;
	object me,ob;
    me=this_player();
	ob=this_object();

	  if( me->query_temp("wzg_baxian")!="go" )
		  return 0;
      if (me->query("wzggive/ludongbin"))
    	{
	 		  message_vision(HIY"\n吕洞宾叹道：若有那"+HIR""+me->query("wzggive/ludongbin")+HIY"就好了．\n"NOR,me);
			  return 1;
		}
	  if( me->query_temp("wzg/ludongbin")!="give")
	    {
	      jname="玄火酒";
		  message_vision(HIY"\n吕洞宾长叹道：" + RANK_D->query_respect(me) + "，近日来我强练镇元神功内息岔乱，已然半身麻痹．
	      只有借助"+HIR""+jname+HIY"之力才能重导内力．要不是练功出岔洞宾
              定然随大家一同前去东海游玩！\n"NOR,me);
		  me->set("wzggive/ludongbin",jname);
		  return 1;
		}
	command("say " + RANK_D->query_respect(me) + "快去叫上其他八仙，说我也同去！\n");
	ob->move("/d/changan/eastseashore");
    return 1;
}

int accept_object(object who, object ob)
{
	  object me = this_object();

	  if( !who->query("wzggive/ludongbin"))
		  return 0;
	  if ((string)ob->query("liquid/name")!=who->query("wzggive/ludongbin"))
   {
     command ("shake "+who->query("id"));
	call_out ("return_ob",1,who,ob);
    return 1;
  }
  
  if (ob->query("liquid/remaining") == 0)
  {
    message_vision (HIY"$N摇了一下头，说道：空的,拿来骗人吗?\n"NOR,me);
    call_out ("return_ob",1,ob,who);
    return 1;
  }
  message_vision(HIY"\n$N接过$n"+HIY"深施一礼道：$N能恢复如此迅速，全靠" + RANK_D->query_respect(who) + "及时送来"+HIR""+who->query("wzggive/ludongbin")+HIY"我们这就动身去东海吧．\n"NOR,me,ob);
  who->set_temp("wzg/ludongbin","give");
  who->delete("wzggive/ludongbin");
  return 1;
}

void return_ob (object who, object ob)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}


string give_book()
{
	object me = this_player();

	if( query("no_book") == 0 )
	{
		carry_object("/d/obj/book/chunyang");
		command("give xinde to " + me->query("id"));
		set("no_book", 1);
		return "吕洞宾说道：好！既然是有心人，那我就给你吧。\n";
	}
	else
	{
		return "吕洞宾说道：太不巧了，我已经送人了。\n";
	}

}

string ask_jinguzhou()
{
	if (this_player() -> query_temp("aware_of_jinguzhou")) 
		return "不都对你说了吗，怎么又来问？\n";
	this_player() -> set_temp("aware_of_jinguzhou", 1);
	command("whisper " + this_player() -> query("id") 
		+ " 听说紫竹林里藏有如来所赐的紧箍咒。");
	return "有缘者得之，无缘者弃之。就看您的福气了。\n";
}