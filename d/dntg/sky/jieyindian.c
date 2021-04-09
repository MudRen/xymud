 // Room: /d/sky/nantianmen
#include <room.h>
#include <ansi.h>
inherit ROOM;

void init();
void close_gate();
int do_knock(string);
int valid_leave();
string look_gate();

void create ()
{
	set ("short", "接引殿");
   set ("long", @LONG

进了南天门，已经可以看到一座座天宫放着七彩霞光，忽隐忽现
于云遮雾绕之中。里壁厢有几根大柱，柱上缠绕着金鳞耀日赤须
龙；一座白玉桥弯弯曲曲地向北延伸，东西两边各有一座大殿，
也不知是干什么用的，你可以隐约听到东边殿中有喧哗之声，似
乎人不少。

LONG);

	set("exits", ([
   	"south" : __DIR__"nantian",
      "north" : __DIR__"caihongqiao",
      "west" : __DIR__"caifengdian",
      "east" : __DIR__"jinlongdian",
]));
	create_door("south", "南天门", "north", DOOR_CLOSED);
   set("no_clean_up", 0);
   setup();
}

void init()
{
   add_action("do_shen", "shen");
}

int err_msg(string arg)
{ 
   write(arg);
   return 1;
}

void finish(object me,object ob)
{
   if( !me || !ob || !present(ob,me) )
   	return;
	message_vision("\n\n"HIC"只见$N"HIC"身上的"+ob->query("name")+HIC"发出一道炫目的霞光！\n\n"NOR,me);
   me->set_temp("block_msg/all", 0);
   ob->level_up();
   tell_object(me,"你从深思中苏醒过来。\n");
   tell_object(me,HIY"你的"+ob->query("name")+HIY"升级了！\n"NOR);
   return;
}               

void do_shen2(string arg,object me,object ob,int price,int temp)
{
	if( !me || !present(me,this_object()) )
		return;
	if( !ob || !present(ob,me) )
	{
		tell_object(me,HIY"你需要升级神马？\n"NOR);		
		return;
	}
	if( arg[0]!='y' && arg[0]!='Y' )
	{
		tell_object(me,HIY"你取消了升级。\n"NOR);
		return;
	}			
	me->add("balance",-price);
	me->add("combat_exp",-temp);
	me->add("daoxing",-temp);
	write("你盘膝而坐，冥思片刻，运转周天玄功，将全身心神关注于"+ob->query("name")+"上。\n");
	message_vision(HIW"只见$N"HIW"泥丸宫一道白气喷出，如光速般向前后左右上下弥漫开来，迅速将其"+ob->query("name")+"笼罩住。\n"NOR,me);
   me->set_temp("block_msg/all", 1);
   me->start_call_out( (: call_other, __FILE__, "finish", me,ob:),3+random(5));
   return;
}

int do_shen(string arg)
{
	object me,ob;
	string s;
   int my_exp,my_dx,my_level,my_balance,temp,price,afford;
   me = this_player();
        
   if( !arg )
   	return err_msg("你要升级什么？\n");
	ob = present(arg,me);
   if( !ob || !ob->is_zhaohuan() )
   	return err_msg("你要升级什么？\n");
	if( ob->query("owner_id")!=me->query("id") )
   	return err_msg(ob->query("name")+"不是你的。\n");
                
	my_exp = me->query("combat_exp");
   my_dx = me->query("daoxing");
   my_balance = me->query("balance");

   if( my_exp < 1000000 || me->query("daoxing") <1000000 )
		return err_msg("你的武学和道行不够100万，暂时不能升级！\n"); 
        
	switch(base_name(ob))
   {
   	case "/obj/armor" :
      	my_level = ob->query("armor_level");
         break;
		case "/obj/weapon" :
      	my_level = ob->query("weapon_level");
         break;
		default :
      	return err_msg(ob->name()+"不能升级。\n");
	}                       
	
   temp=(my_level+1)*(my_level+1)*100;
   if(my_balance>10000000)
   { 
   	if(my_exp>=temp||my_dx>=temp)
      {
			price=10*10000*(my_level+1);              
         if((my_balance)<price)
         	price = my_balance;
                        
         if( my_level<=500 )
         {
         	if(my_level<10)
            	temp = 10000;
				else	
					temp=(my_level+1)*(my_level+1)*100;
          }
          else    temp=30000000;
                        s = MONEY_D->money_str(price);
                        s = COLOR_D->clean_color(s);
                        write(HIY"你升级"+ob->query("name")+"需要消耗:"+s+"存款、"+temp+"点武学与道行。\n"NOR);
                        write(HIY"你确定升级吗？(y/n):"NOR);
			input_to( (: do_shen2 :), me,ob,price,temp );                        
                        return 1;
                }
                else    return err_msg(HIY"你的武学或道行不够，需要消耗你的武学与道行"HIM+temp+HIY "点！\n" NOR);
        }
        else    return err_msg("你的在钱庄的存款不够升级喽！\n ");
}
	