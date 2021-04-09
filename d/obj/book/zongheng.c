// zongheng, 1-60
// zongheng-sword.c
//  by 凌惊雪 5-4-2002 

inherit ITEM;
#include <ansi.h>
void init();
int do_read(string arg);

void create()
{
        set_name(HIR"《纵横剑法秘籍》"NOR, ({"zongheng miji","zongheng","miji","book"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "册");
	set("long",
	"一本小册子，封面上《纵横剑法》龙飞凤舞，气势不凡。\n");
        set("material", "paper");
        set("no_put",1);
        set("no_give",1);
	set("no_drop", 1);                
        set("no_get",1);
        set("value", 0);
        }
}

void init()
{
	add_action("do_read", "read");
	add_action("do_read", "study");
}
int do_read(string arg)
{
	object me;
	int sen_cost, gain;
	
	me=this_player();

    	if( !this_object()->id(arg) ) return 0;
	if(me->query("family/family_name")!= "百花谷")        
	        	return notify_fail("上面的东西你似乎看不懂？");
    	if( !me->is_knowing("bhg_zongheng") )
    	                return notify_fail("你哪儿偷来的书？\n"); 
    	if( me->is_busy() )
        		return notify_fail("你现在忙着呢，哪有可能静心研读...\n");
   	if( me->is_fighting() )
        		return notify_fail("现在才想到精研纵横剑法，太晚了吧？\n");
	if( (int)me->query_skill("literate", 1) < 50 ) 
		return notify_fail("你看了半天，里面不少字都是它认得你你不认得它。\n");
	if( (int)me->query_skill("zongheng-sword",1)>200 )
		return notify_fail("你在纵横剑法方面已经很有造诣，这本书不会让你长进多少。\n");

	sen_cost = 25 + random((30-(int)me->query("int")));
	if( sen_cost < 10 ) sen_cost = 10;
	if( (int)me->query("sen")<sen_cost )
		return notify_fail("你现在头晕脑胀，该休息休息了。\n");	
	me->receive_damage("sen", sen_cost);

	gain = (int)me->query_skill("literate", 1)/5+(int)me->query("int")/4+1;
	me->improve_skill("zongheng-sword", gain);

	message_vision("$N研究纵横剑法秘籍，似乎有所领悟。\n", me);
		
	return 1;
}

