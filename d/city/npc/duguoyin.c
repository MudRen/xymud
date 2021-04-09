// 杜过瘾，duguoyin.c 
// 5-3-97, pickle

inherit NPC;

void create()
{
  set_name("杜过瘾", ({"du guoyin", "du", "guoyin", "duguoyin", "boss"})); 
  set("gender", "男性" );
  set("age", 52);
  set("title", "赌场老板");
  set("long","这老头看起来一脸悠闲，时不时抬头看看四个桌子上的赌客。");
  set("combat_exp", 40000);
  set("daoxing", 20000);

  set_skill("dodge", 50);
  set_skill("parry", 50);
  set_skill("unarmed", 50);
  set_skill("literate", 70);
  set("attitude", "friendly");
  set("rank_info/respect", "孔秀才");
  set("per",25);
  set("vendor_goods", ([
    "xiji": "/d/obj/books-nonskill/xiji",
    "fuji": "/d/obj/books-nonskill/fuji",
    "kunlun": "/d/obj/books-nonskill/kunlun",
    "san": "/d/obj/book/san",
    "blade-book" : "/d/obj/book/basic_blade",
    "unarmed-book": "/d/obj/book/basic_unarmed",
   ]));
  setup();
  carry_object("/d/obj/cloth/choupao")->wear();
}

void init()
{
  object ob;

  ::init();
  if( interactive(ob = this_player()) && !is_fighting() ) {
    remove_call_out("greeting");
    call_out("greeting", 1, ob);
  }
  add_action("do_vendor_list", "list");
}

void greeting(object ob)
{
  if( !ob || !visible(ob) || environment(ob) != environment() ) return;
  command("say 这位" + RANK_D->query_respect(ob) +"请进请进。\n");
}
/*
mixed buy_object (object who, object item)
{
  object npc = this_object();
  string st;

  st= "total"+(string)item;
  if (npc->query_temp("total_books") < 30)
      {
	if (npc->query_temp(st)<10)
	  {
	    npc->add_temp(st,1);
  	    return ::buy_object(who,item);
	  }
	else
	  {
	    return notify_fail("孔方兄说道：对不起，您老要的书卖完了！您等下一批进货吧。\n");
	  }
	npc->add_temp("total_books", 1);
      }
      else
      {
	return notify_fail("孔方兄说道：小店本小，今日以将存货卖完了。您老等下一批吧。\n");
      }
    }
*/