// by snowtu
#include <ansi.h>
inherit NPC;
#include "colors.h"

int test_player();

void create()
{
  set_name("殷温娇", ({"yin wenjiao", "yin", "wenjiao"}));
  set("long", "殷夫人乃是殷开山之女，玄奘之母。\n");
  set("title", "御赐贤夫人");
  set("gender", "女性");
  set("age", 50);
  set("per", 35);
  set("attitude", "peaceful");
  set("shen_type", 1);
  set("combat_exp", 10000);
  set_skill("unarmed", 40);
  set_skill("dodge", 40);
  set_skill("parry", 40);
  set_skill("force", 40);
  set_skill("spells", 40);
  set("max_gin",300);
  set("max_kee",300);
  set("max_sen",300);
  set("max_force",300);
  set("max_mana",300);
  set("force_factor",5);
  set("inquiry", ([
        "here":   "此乃禹王台也，水陆大会将不期举行，妾身在此预做法场以事天下灾民难民。\n",
        "name":   "玄奘之母殷夫人也，在此做法以事天下灾民难民。\n",
        "give":   (: test_player() :),
        "灾民":   (: test_player() :),
        "难民":   (: test_player() :),
        "穷人":   (: test_player() :),
        "受灾":   (: test_player() :),
        "解难":   (: test_player() :),
        "救灾":   (: test_player() :),
        "救":   (: test_player() :),
        "给":   (: test_player() :),
      ]));
  setup();
  carry_object("/d/obj/cloth/skirt")->wear();
  carry_object("/d/obj/cloth/shoes")->wear();
}

void rewarding (object who)
{
  object me = this_object();
  string reason;
  int reward;

  reason = "救人之急，为"+who->query("quest/pending/give/ture_name")+"送去"+who->query("quest/pending/give/object_turename")+"，";
  message_vision ("$N对$n说道：多谢这位"+RANK_D->query_respect(who)+reason+"真是品行可嘉也。\n",me,who);
  reward = quest_reward(who, "give");
  who->add("quest/reward",reward);
  who->set("quest/reason",reason);
  if( who->query("quest/give/level")>=10 )
  	who->set("quest/give/level",1);
  else
  	who->add("quest/give/level",1);	  
  who->add("quest/give/times",1);
  who->add("quest/give/reward",reward);
  who->delete("quest/pending/give");
  quest_done(who);
}

void check_player (object who)
{
  object me = this_object();
  int t;

  if (!who || !visible(who))
      return;

  if (! who || environment(who)!=environment(me))
    return;

  if (who->query("quest/reward") > 0)
  {
    message_vision ("$N对$n说道：这位"+RANK_D->query_respect(who)+"身上祥云环绕，请速赴长安进宫请赏！\n",me,who);
    return;
  }

  if (! who->query("quest/pending/give"))
    return;

  if (! who->query("quest/pending/give/done"))
  {
    message_vision(who->query("quest/pending/give/msg"),me,who);
    return;
  }

  t = who->query("quest/pending/give/time");

  if (t >= uptime() && (t-MAXDELAY) <= uptime())
  {
    message_vision ("$N对$n惊叹道：您已经回来了？不会这么快吧。\n",me,who);
    message_vision ("$N看了一眼香说道：这香还需"+chinese_number((t-uptime())/60+1)+"分钟才燃尽，到时您再来吧。\n",me,who);
    return 0;
  }
  rewarding (who);
}

void init ()
{
	if( userp(this_player()) )
		check_player(this_player());
}

int test_player()
{
  mapping obj_msg,npc_msg;	
  string name,obj_name;	
  string t_name,t_id,t_where,t_long;	
  string msg,file,*strs = ({
    "$N拿起一根签，对$n说道：近闻他乡受灾，妾身正想请人去给$w送$o。\n",
    "$N对$n点点头说道：妾身刚求了一签，知道$w有难，正想送$o去。\n",
    "$N对$n说道：正好正好，妾身占签得知$w现急需$o。\n",
    "$N不语，从盒里小心抽出一签，缓缓地对$n说：现闻$w需要$o。\n",
    "$N点点头，舒袖将手中的签打开，惊叹道：有$w正急需$o也。\n",
    "$N从打开签盒取出一签对$n说道：他乡有难，请去给$w送$o。\n",
    "$N将手中签细细一读，对$n说道：签曰现有$w急需$o。\n",
    "$N一扬签对$n说道：事不宜迟请去给$w送$o。\n",
  });  
  int i;
  object npc,ob,*temp,*obj,who,me = this_object();
  
  who = this_player();
  
  if( who->query("quest/reward") > 0)
    return err_msg(name()+"对你说道：这位"+RANK_D->query_respect(who)+"，妾身见你身上祥云环绕，何不去从速赴长安进宫请赏？\n");
  if( who->query("quest/pending/give"))
  {
  	if( who->query("quest/pending/give/done") )
  	{
  		rewarding (who);
  		return 1;
  	}
        message_vision(who->query("quest/pending/give/msg"),me,who);
  	return 1;
  }
//NPC
  file = npc_file[random(sizeof(npc_file))];
  obj = children(file);
  if( !obj || !arrayp(obj) )
    return err_msg(name()+"对你叹气说道：这位"+RANK_D->query_respect(who)+"该做的事做了不少，妾身看您还是以后再来吧。\n");
  temp = ({});
  for(i=0;i<sizeof(obj);i++)
  {
  	if( !environment(obj[i]) )
      continue;
    temp+= ({obj[i]});
  }
  if( sizeof(temp)<1 )
    return err_msg(name()+"叹气道：这位"+RANK_D->query_respect(who)+"该做的事做了不少，妾身看您还是以后再来吧。\n");
  
  npc = temp[random(sizeof(temp))];  
  npc_msg = query_obj_msg(npc,1);
  if( !npc_msg || !mapp(npc_msg) )
  {
    return err_msg(name()+"叹了一口气，说道：这位"+RANK_D->query_respect(who)+"该做的事做了不少，妾身看您还是以后再来吧。\n");  
  }
//give_OBJ  
  if( random(2) )
  	file = cloth_file[random(sizeof(cloth_file))];
  else if( random(2) )
  	file = armor_file[random(sizeof(armor_file))];	
  else	
  	file = food_file[random(sizeof(food_file))];
  	
  ob = new(file);	
  obj_msg = query_obj_msg(ob,2);
  if( !obj_msg || !mapp(obj_msg) )
  {
  	if( ob ) destruct(ob);
    return err_msg(name()+"叹了一口气，说道：这位"+RANK_D->query_respect(who)+"该做的事做了不少，妾身看您还是以后再来吧。\n");  
  }
  name = npc_msg["who_name"]+"的"+npc_msg["obj_name"]+"("+npc_msg["obj_id"]+")";
  obj_name = obj_msg["obj_name"]+"("+obj_msg["obj_id"]+")";
  msg = strs[random(sizeof(strs))];
  msg = replace_string(msg,"$w",name);
  msg = replace_string(msg,"$o",obj_name);
  message_vision(msg,this_object(),who);
  
  who->set("quest/pending/give",([
  	"name" : npc_msg["obj_name"],
  	"id"   : npc_msg["obj_id"],
  	"ture_name" : npc_msg["ture_name"],
  	"ture_id"   : npc_msg["ture_id"],
  	"file" : base_name(npc),
  	"obj_file" : base_name(ob),
  	"msg"  : msg,
  	"objectname": obj_msg["obj_name"],
  	"objectid"  : obj_msg["obj_id"],
  	"object_turename": obj_msg["ture_name"],
  	"object_tureid" : obj_msg["ture_id"],
  	"time" : time(), 
  ]));	 	        	   
  who->save();
  me->delete_temp("random_rel");
  if( ob )  destruct(ob);
  return 1;
}
