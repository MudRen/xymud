//created 6-9-97 pickle
//亲兵
 
inherit NPC;

void create()
{
  set_name("亲兵", ({"qin bing", "qin", "bing", "soldier", "qinbing"}));
  set_level(16);
  set ("long", @LONG
一个彪形大汉，看身上衣服大概是齐府的亲兵，齐王李建成的近身护卫。
LONG); 
  set("title", "齐王府");
  set("gender", "男性");
  set("age", 25);
  set("per",15+random(5));
  set_skill("blade", 160);
  set_skill("dodge", 160);
  set_skill("parry", 160);
  set_skill("wuhu-blade", 160);
  map_skill("blade", "wuhu-blade");
  set("inquiry", ([
        "name" : "问什么问？长着眼睛不会看哪？",
        "here" : "这儿就是醉星楼！造的可比对面那破房子强得多啦！",
        "rumors" : " 听说有人想来拆房子，哼！",
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
 
  if ((string)ob->query("name_recognized")!="齐府令箭")
    {
      command ("say 哈哈！老子最爱受人贿络了！");
      call_out("destroy", 1, ob);
      return 1;
    }
  call_out("leavehere", 2, npc, me);
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







