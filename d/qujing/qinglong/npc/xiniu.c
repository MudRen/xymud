// created by snowcat on 12/5/1997

inherit NPC;

void create()
{
  int i = 40+random(10);
  set_name("守门牛精", ({"shoumen niujing", "niujing", "jing"}));
  set("gender", "男性");
  set_level(i);
  set("age", 20*i);
  set("long","一个守卫内宫的妖精。\n");
  set("per", 15);
  set_skill("parry", 10*i);
  set_skill("blade", 10*i);
  set_skill("unarmed", 10*i);
  set_skill("dodge", 10*i);
  set("force_factor",20*i);
  setup();
  carry_object(0,"blade",random(2))->wield();
  carry_object("/d/obj/cloth/shoupiqun")->wear();
}

void die ()
{
  object me = this_object();
  object where = environment (me);
  object bone = present ("bone 4",where);

  if (! bone)
  {
    bone = new ("/d/obj/misc/bone");
    bone->move(where);
  }

  message_vision ("\n$N倒了下去，化为一堆兽骨。\n",me);  
  if (! present("shoumen niujing 4",where))
  {
    object ob = new ("/d/qujing/qinglong/npc/xiniu");
    ob->move(where);
    message_vision ("\n从里面又蹿出一位$N！\n",me);   
  }
  destruct (me);  
}

void unconcious ()
{
  die();
}

void return_ob (object ob, object who)
{
  if (ob)
    command ("give "+ob->query("id")+" to "+who->query("id"));
}

void destruct_me (object ob)
{
  destruct (ob);
}

int accept_object (object who, object ob)
{
  object me = this_object();

  if (ob->query("name") != "油葫芦")
  {
    message_vision ("$N摇了一下头，说道：不要。\n",me);
    call_out ("return_ob",1,ob,who);
    return 1;
  }
  if (ob->query("liquid/remaining") == 0)
  {
    message_vision ("$N摇了一下头，说道：油葫芦是空的。\n",me);
    call_out ("return_ob",1,ob,who);
    return 1;
  }
  message_vision ("$N说道：谢谢！\n",me);
  who->set_temp("obstacle/jinping_give_hulu",1);
  call_out ("destruct_me",1,ob);
  return 1;
}