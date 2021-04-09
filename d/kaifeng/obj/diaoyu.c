// created by snowcat 

inherit ITEM;

void create()
{
  set_name("雕玉箱", ({ "diaoyu xiang", "xiang" }) );
  set_weight(250000);
  set_max_encumbrance(8000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "个");
    set("long", "这是一个沉重的雕玉箱，可以往里面募捐(donate)些银两。\n");
    set("value", 2000);
  }
}

int is_container()
{
  return 1;
}

void init ()
{
  add_action ("do_donate","donate");
}

int do_donate (string arg)
{
  object who = this_player ();
  int v;
  
  if( !arg ) 
        return 0;
  if( sscanf(arg,"%d %s",v,arg)!=2 )
        return notify_fail("你要捐多少？\n");
  if( v<=0 ) 
        return notify_fail("你要捐多少？\n");                   
  switch(arg)
  {
        case "gold" : v = v*10000;break;
        case "silver" : v = v*100;break;
        case "coin" : v = v; break;
        default : return notify_fail("你要捐多少？\n");
  }
  if( v<100 )
        return notify_fail("不要太抠门了。\n");
  if( !who->check_pay(v) )
        return notify_fail("你身上没有这么多钱。\n");
                
  who->add_temp("kaifeng_donate_silver", v);
  who->money_add(-v);   
  message_vision ("$N从身上取出"+MONEY_D->money_str(v)+"放到雕玉箱里。\n",who);  
  
  if( v/10 )
        who->add_temp("kaifeng_donate_silver", v/10);
  else  who->set_temp("kaifeng_donate_silver", 1);
  
  if( v/10>0)
        write("好！你在宫中三拜所需的时间将减少"+chinese_number(v*3/10)+"秒！\n");
        
  return 1;
}


