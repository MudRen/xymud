// rewritten by snowcat.c 4/4/1997
// niuer.c
#define NAME "牛二先生"

inherit NPC;

int is_busy;
int is_empty;

void create()
{
  set_name(NAME, ({"niuer","xiansheng","daoshi"}));
  set_level(800);
  set("gender", "男性" );
  set("age", 53);
  set("title", "如意真仙");
  set("long", "牛二先生是牛魔王的弟弟。不过他一向不喜欢别人叫他\n牛二先生，而喜欢被叫作如意先生。");
  set("class","taoist");

  set("attitude", "peaceful");
  set_skill("unarmed",800);
  set_skill("dodge",800);
  set_skill("parry",800);
  set_skill("spells",800);
  set("per", 35);
  set("inquiry", ([
        "name": "我是牛魔王的弟弟，别人叫我如意先生。\n",
        "如意先生": "如意，如意，我有时候常常治一些肚子不舒服的毛病。\n",
        "肚子": "肚子胀，肚子大，肚子痛我都可以试一试。\n",
  ]));
  setup();
  carry_object("/d/obj/cloth/taijicloth")->wear();
  is_busy = 0;
  is_empty = 0;
}


int accept_money (object who,int v)
{
  object queen;
  string msg, id;
  int amount;
  msg = NAME+"拱手道：这位"+RANK_D->query_respect(who);

  amount = v;

  if (who->query("obstacle/nuerguo") == "done")
  {
    queen = new (__DIR__"queen");
    queen->refuse_player (who);
    destruct (queen);
    say(msg+"，咳……说的也是。\n");
    return 1;
  }  

  if (who->query("obstacle/nuerguo") == "marriage")
  {
    say(msg+"还是先去见公主吧。\n");
    return 1;
  }  

  if (who->query("obstacle/nuerguo") == "company")
  {
    say(msg+"还是先去见公主吧。\n");
    return 1;
  }  

  if (who->query("obstacle/nuerguo") != "stomachache")
  {
    say(msg+"看来没什么毛病。\n");
    return 1;
  }
  
  if ( v < 30000) 
  {
    say(msg+"，咳……这个……怕是不妥吧。\n");
    return 1;
  }  

  if (is_busy)
  {
    say(msg+"，真对不起，我不正在忙着治病吗？\n");
    return 1;
  }  
  if (is_empty)
  {
    say(msg+"，对不起，治病的泉水用完了，等一会儿再来吧。\n");
    return 1;
  }  

  say(msg+"真是太客气了，我这就给您治病。\n");
  is_busy = 1;
  is_empty = 1;
  call_out("get_water",1,who);
  call_out("get_water",15,who);
  call_out("heal_stomach",30,who);
  who->start_busy(30,30); // will be reset when heal
  remove_call_out("reset_busy");
  call_out("reset_busy",30);
  remove_call_out("reset_empty");
  call_out("reset_empty",1800);
  return 1;
}

void get_water (object who)
{
  if (who)
  {
    say ("\n"+NAME+"慢悠悠地走过去，吱吱嘎嘎地摇上一桶泉水。\n\n");
    call_out("pour_water",1,who);
  }
}

void pour_water (object who)
{
  if (who)
  {
    say (NAME+"拿起一只金药盅，口中念念有词。\n");
    say ("只见满满一大桶水居然全部都倒进小药盅里！\n\n");
    call_out("feed_water",1,who);
    call_out("feed_water",2,who);
    call_out("feed_water",3,who);
  }
}

void feed_water (object who)
{
  if (who)
  {
    message_vision (NAME+"捧起金药盅，将泉水慢慢灌进$N的嘴里。\n",who);
    message_vision ("一股凉意流进$N的体内，$N的肚子里动了一下。\n",who);
  }
}

void heal_stomach (object who)
{
  int res;

  if (! who)
    return;

  if (random(10)==0)
  {
    message_vision ("\n$N猛咳了几下，嘴里呛出一些淡黄色的水！\n",who);
    res = 1;
  }
  else
  {
    message_vision ("\n$N奋力张了张嘴，想咳出什么，可什么都没咳出来。\n",who);
    res = 0;
  }
  call_out("check_result",1,who,res);
}

void check_result (object who, int res)
{
  object queen;

  if (! who)
    return;

  if (res)
  {
    say (NAME+"脸上露出了微笑：看样子药性极佳，治好了。\n");
    queen = new (__DIR__"queen");
    queen->announce_success (who,"治好了腹水孕");
    destruct (queen);
  }
  else
  {
    say (NAME+"叹了一口气：嗯，没有治好，还得再来看一次。\n");
  }
  who->interrupt_me();
}

void reset_busy ()
{
  is_busy = 0;
}

void reset_empty ()
{
  is_empty = 0;
}