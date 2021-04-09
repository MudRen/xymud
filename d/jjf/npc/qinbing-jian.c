//created 6-9-97 pickle
//亲兵

#include <ansi.h>
inherit NPC;
string ask_me(object me);

void create()
{
  set_name("亲兵", ({"qin bing", "qin", "bing", "soldier", "qinbing"}));
  set_level(18);
  set ("long", @LONG
一个彪形大汉，看身上衣服大概是建府的亲兵，乃是高祖
第三子李元吉的近身护卫。他除了保护李元吉外似乎还管
发散钱财吃喝。
LONG); 
  set("title", "建王府");
  set("gender", "男性");
  set("age", 25);
  set("per",15+random(5));
  set_skill("blade", 180);
  set_skill("dodge", 180);
  set_skill("parry", 180);
  set_skill("wuhu-blade", 160);
  map_skill("blade", "wuhu-blade");
  set("inquiry", ([
        "name" : "问什么问？长着眼睛不会看哪？",
        "here" : "这儿就是醉星楼！造的可比对面那破房子强得多啦！",
        "rumors" : " 听说有人想来拆房子，哼！",
        "食物" : "如果是良民，可以领些包子去。",
        "钱财" : "如果是良民，可以领些银子去。",
        "包子" : (: ask_me :),
        "baozi" : (: ask_me :),
        "拆房子" : "哼，除非把老子打发了，否则谁也别想来这儿撒野！",
         ]) );
  set("chat_msg_combat", ({
        	(: perform_action, "blade", "duan" :),
  }) );         
  setup();
  carry_object(0,"blade",random(3))->wield();
  carry_object(0,"armor",random(3))->wear();
  carry_object(0,"pifeng",random(3))->wear();
}

int accept_object(object me, object ob)
{
	object npc=this_object();
 	if ((string)ob->query("name_recognized")!="建府令箭")
    	{
      		command ("say 哈哈！老子最爱受人贿络了！");
      		call_out("destroy", 1, ob);
      		return 1;
    	}
  	call_out("leavehere", 1, npc, me);
  	return 1;
}

string ask_me(object me)
{
	return("可以从我这里领到(ling)包子。");
}

void init()
{
	add_action("do_ling", "ling");
}

int do_ling(string arg)
{
	object me=this_player(), npc=this_object(),ob;
  	int kar=me->query_kar();
  	string player=me->query("id");

  	if (!arg || (arg != "baozi" && arg != "包子" ))
		return notify_fail("你想要什么？\n");
  	if ((string)me->query("family/family_name") == "将军府")
    	{
       		me->add_temp("jjf/醉星楼要东西", 1);
       		switch(me->query_temp("jjf/醉星楼要东西"))
         	{
           		case(1):
             			EMOTE_D->do_emote(this_object(), "slap",geteuid(ob),CYN,0,0,0);
				command("say 呔！二位王爷最恨的就是将军府弟子！给我滚！");
                		message_vision(CYN"亲兵飞起一脚踢在$N屁股上，将$N踢出门外。\n"NOR, me);
                		me->move("/d/city/center");
                		return 1;
             		case(2):
             			EMOTE_D->do_emote(this_object(), "slap",geteuid(ob),CYN,0,0,0);
                		command("say 莫要敬酒不吃吃罚酒！再来一次可别怪老子不客气了！");
                		message_vision(CYN "亲兵飞起一脚踢在$N屁股上，将$N踢出门外。\n" NOR, me);
                		me->move("/d/city/center");
                		return 1;
            		default:
             			command("say 又是你！老子看你实在不顺眼，去死吧！");
                		kill_ob(me);
                		return 1;
		}
	} 
	if ((string)me->query("title") != "普通百姓")
    	{
      		EMOTE_D->do_emote(this_object(), "pei",geteuid(ob),CYN,0,0,0);
      		command("say 混帐！有本事的自己干活去！");
      		return 1;
    	}
	if( kar>30 )  kar = 30;
      	if (me->query("kee") < 40 || me->query("sen") < 40)
		return notify_fail("你太累了，挤不到亲兵边上。看来包子拿不到了。\n");
	ob=new("/d/obj/food/baozi");
      	ob->move(npc);
      	command("say 好吧，就赏你个包子吧！别忘了是谁给你的好处！");
      	me->receive_damage("kee", 40-kar);
      	me->receive_damage("sen", 40-kar);
      	message_vision("$N费尽九牛二虎之力，被挤得浑身酸痛，才从人群中挤到亲兵面前。\n",me);
      	command("give bao to "+player);
      	return 1;
}

void leavehere(object npc, object me)
{
  command("ah");
  command("say 既然齐王有急事，我这就去办！");
  command("thank "+me->query("id"));
  command("go northwest");
  destruct(npc);
  return;
}
void destroy(object ob)
{
  destruct(ob);
  return;
}