//碧藕


#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
    set("no_get","你手里一松"+this_object()->query("name")+"丹从指间滑落！\n");
    set("no_give","这么珍贵的药，哪能随便给人？\n");
    set("no_drop","这么宝贵的丹药，扔了多可惜呀！\n");
    set("no_sell","凡人哪里知道"+this_object()->query("name")+"的价值？还是自己留着吧。\n");
  }                                    
  add_action("do_eat", "eat");
}

void create()
{
  set_name(YEL "交梨" NOR, ({"jiao li","li"}));
  set_weight(200);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "枚");
    set("long", "一枚采自海中仙山，香气扑鼻的交梨。\n");
    set("value", 0);
    set("drug_type", "补品");
  }
  
  // the following line is added by snowcat
  set("is_monitored",1);
  setup();
}

int do_eat(string arg)
{
  object me = this_player();
  int mana_add, force_add, howold;
  howold = (int)me->query("mud_age") + (int)me->query("age_modify");
  if (!id(arg))
    return notify_fail("你要吃什么？\n");
  
  me->set("food", (int)me->max_food_capacity());
  me->set("water", (int)me->max_water_capacity());
  mana_add = 2;
  force_add = 2;
  me->add("eat_jiaoli", 1);
  if ( (int)me->query("eat_jiaoli") > 10) {
    if( (int)me->query("maximum_force") > 100 ) {
      me->add_maximum_force(-3);
    }
    if( (int)me->query("maximum_mana") > 100 ) {
      me->add_maximum_mana(-3);
    }
    me->delete("eat_jiaoli");
    message_vision(HIG "$N吃下一枚交梨，脸色突然急变，「哇哇」几口又吐了出来！\n" NOR, me);
    tell_object(me,BLK "你口中有一股说不出的味道，这枚交梨原来生了虫了！\n" NOR);
  }
  else if( me->add_maximum_mana(mana_add) ||
    me->add_maximum_force(force_add)) {
    message_vision(HIG "$N吃下一枚交梨，两眼炯炯放光！\n" NOR, me);
  }
  else message_vision(HIG "$N吃下一枚交梨，嚼也没嚼连核吞了下去！\n" NOR, me);
  
  if( howold > 1382400 ) {
    me->add("age_modify",250000);
    me->add("age_modify_time", 1);
  }
  destruct(this_object());
  return 1;
}

