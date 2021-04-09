// created 4/12/1998 by bbs
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
int tell_test();
int do_drop(object, object);

void create()
{
  set_name("哪吒", ({ "nezha santaizi", "nezha", "santaizi" }));
  set("title", "三坛海会之神");
  create_family("陷空山无底洞", 1, "弟子");
  set("class", "xian");
  set("long", "一位唇红齿白的美少年。\n");
  set("gender", "男性");
  set("age", 16);
  set("attitude", "heroism");
  set("rank_info/respect", "小太子");
  set("rank_info/rude", "乳臭未干的小儿");
  set_level(170);
  set("force_factor", 100);
  set("mana_factor", 120);
  set("daoxing", 3000000);

  set_skill("spells", 1700);
  set_skill("dao", 1700);
  set_skill("unarmed", 1700);
  set_skill("yinfeng-zhua", 1700);
  set_skill("dodge", 1700);
  set_skill("lingfu-steps", 1700);
  set_skill("parry", 1700);
  set_skill("force", 1700);
  set_skill("huntian-qigong", 1700);
  set_skill("blade", 1700);
  set_skill("sword", 1700);
  set_skill("qixiu-jian", 1700);
  map_skill("spells", "dao");
  map_skill("unarmed", "yinfeng-zhua");
  map_skill("parry", "huoyun-qiang");
  map_skill("sword", "qixiu-jian");
  map_skill("dodge", "lingfu-steps");
  map_skill("force", "huntian-qigong");
  set("inquiry", ([
	"name": "我乃托塔天王三太子李哪吒是也。",
	"here": "这里是托塔天王府。",
	//"金砖"     : (: tell_test :),
	"rumors": "玉帝敕封家严为降魔大元帅，在下为三坛海会之神，专管降妖除魔。",
	"玉鼠精": "无底洞的玉鼠精？那是我爹的义女。",
	"火尖枪": "送人了！",
	]));
  set("env/test",({"HIY","HIB","HIR"})[random(3)]);
  set_temp("weapon_level",110);
  set_temp("armor_level",110);	
  setup();
  carry_object(0,"cloth",1)->wear();
  carry_object(0,"armor",1)->wear();
  carry_object(0,"sword",1)->wield();
  if ("/d/obj/fabao/huntian-ling"->in_mud())
    carry_object("/d/obj/fabao/huntian-fake");
  else
    carry_object("/d/obj/fabao/huntian-ling");
  if ("/d/obj/fabao/qiankun-quan"->in_mud())
    carry_object("/d/obj/fabao/qiankun-fake");
  else
    carry_object("/d/obj/fabao/qiankun-quan");
  powerup(1);  
}

void die()
{
  int i;
  object *inv;
  string msg;

  if(environment()) {
    msg="$N恨恨地道：小爷我这就去告御状，有种你就在这儿等着！\n";
    msg+="$N化道金光，径往南天门方向而去。\n\n";
    message_vision(msg, this_object(), this_player());
    inv=all_inventory(this_object());
    for(i=0; i<sizeof(inv); i++) {
      if (inv[i]->query("no_drop")) continue;
      do_drop(this_object(), inv[i]);
    }
  }
  destruct(this_object());
}

int do_drop(object me, object obj) 
{
  if (obj->move(environment(me))) {
      //d_mana>0 is for "bian". mon 11/05/97
      if((obj->query_temp("d_mana"))>0) {
            if( obj->query_temp("is_living")==1 )
                 message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
            else {
                 message_vision( sprintf("$N丢下一%s$n。\n", undefinedp(obj->query_temp("unit"))? "个":obj->query_temp("unit") ), me, obj );
           }
      } else {
           if( obj->is_character() )
                  message_vision("$N将$n从背上放了下来，躺在地上。\n", me, obj);
           else {
             message_vision( sprintf("$N丢下一%s$n。\n", obj->query("unit")), me, obj );
             if( !obj->query("value") && !obj->value() ) {
                tell_object(me,"因为这样东西并不值钱，所以人们并不会注意到它的存在。\n");
                destruct(obj);
             }
           }
      }
      return 1;
  }
  return 0;
}

void unconcious()
{
    die();
}