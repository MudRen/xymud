#include <ansi.h>
inherit ITEM;
void init()
{
      	if(this_player()==environment())
        add_action("do_yandu", "yandu");
      	call_out("announce",random(10),this_player());
}
void announce(object who)
{
    	if(!this_object()) 
    		return;
    	if(!who) 
    		return;
    	CHANNEL_D->do_channel(this_object(), "rumor", 
            who->query("name")+"得到了失落多年的"+name()+"！\n");
}
void create()
{
        set_name(YEL "《八卦秘诀》" NOR, ({"bagua mijue", "mijue"}));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
		set("no_drop",1);
		set("no_get",1);
                set("long", "一本记录万寿山五庄观武功和阵法的经书，上面氤氲袅绕。。。\n");
                set("value", 10000);
        }
  
        set("is_monitored",1);
        setup();
}
int do_yandu(string arg)
{
        object me = this_player();
        if (!id(arg)) 
        	return notify_fail("你要读什么？\n");
        if (me->query("family/family_name")!="五庄观") 
        	return notify_fail("这本书你读不来的!\n");
        message_vision(HIB "$N迫不及待地翻阅着《八卦秘诀》！ \n" NOR, me);  
	me->set("daemon/mijue_wzg","get");
	me->add("daoxing",random(3000));
	me->add("potential",random(3000));
	me->add("combat_exp",random(3000));
	log_file("static/mijue1","["+ctime(time())+"] "+
        sprintf("%s(%s)读了%O\n",
         this_player()->query("name"),this_player()->query("id"),
 this_object()));
        
        tell_object (me,"你仿佛对万寿山五庄观武功和阵法的领悟进入了一个新的境界。\n");
        destruct(this_object());
        return 1;
}
