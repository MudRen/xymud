// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>
#include <armor.h>
inherit NECK;

void create()
{
	string msg;
	seteuid(getuid());
	switch (random(14))
  	{
    		case 0:set_name(HIB "蓝玫瑰" NOR, ({ "flower"})); break;
    		case 1:set_name(HIB "黑郁金香" NOR, ({ "flower"})); break;
    		case 2:set_name(HIB "薄雪花" NOR, ({ "flower"})); break;
    		case 3:set_name(HIB "野风信子" NOR, ({ "flower"})); break;
    		case 4:set_name(HIB "玉白露" NOR, ({ "flower"})); break;
    		case 5:set_name(HIB "睡芙蓉" NOR, ({ "flower"})); break;
    		case 6:set_name(HIB "紫蔷薇" NOR, ({ "flower"})); break;
    		case 7:set_name(HIB "大丽花" NOR, ({ "flower"})); break;
    		case 8:set_name(HIB "勿忘我" NOR, ({ "flower"})); break;
    		case 9:set_name(HIB "白玫瑰" NOR, ({ "flower"})); break;
    		case 10:set_name(HIB "翡翠绿" NOR, ({ "flower"})); break;
    		case 11:set_name(HIB "雪腊梅" NOR, ({ "flower"})); break;
    		case 12:set_name(HIB "曼陀罗" NOR, ({ "flower"})); break;
    		default:set_name(HIB "睡莲" NOR, ({ "flower"})); break;
    	}
  	set_weight(100);
  	set("level",5);
  	set("long","一朵色彩艳丽的"+query("name")+"。\n");
  	set("unit", "朵");
  	set("armor_prop/armor", 1);
  	set("armor_prop/personality", 1);
	switch (random(9))
  	{
    		case 0:msg = "$N戴上一朵$n，不禁想起年少时曾经的梦中人。\n"; break;
    		case 1:msg = "$N戴上$n，沉默几许……低首往事如烟。\n"; break;
    		case 2:msg = "$N拿起$n插在发际，婉尔一笑。\n"; break;
    		case 3:msg = "$N将一朵$n别在胸前，禁不住泪如雨下。\n"; break;
    		case 4:msg = "$N将$n别在胸前，那个熟悉的名字脱口而出。\n"; break;
    		case 5:msg = "$N将$n插在胸前，心里不禁一热。\n"; break;
    		case 6:msg = "$N将$n拿起来，忘情地一吻，然后插在胸前。\n"; break;
    		case 7:msg = "$N小心地把$n别在发鬏上。\n"; break;
    		default:msg = "$N将长发轻轻一甩，将$n别在上面。\n"; break;
	}
  	set("wear_msg",msg);  
  	set("unequip_msg","$N将$n轻轻地摘下来……\n");	
  	setup();
  	set_heart_beat(15+random(20));
}

void init ()
{
	set("water",0);
  	add_action ("do_smell", "smell");
  	add_action ("do_smell", "wen");
  	add_action ("do_water", "water");
  	add_action ("do_fix", "fix");
}

int do_smell (string arg)
{
  	object me = this_player();
  	object flower = this_object();
  	string name = flower->query("name");
  	string msg;

  	if( !arg || !id(arg) )
    		return 0;
    	if( me->is_busy() )
    		return err_msg("你现在正忙。\n");	
	switch (random(9))
  	{
    		case 0: msg = "$N闻了闻"+name+"，想起当年那好熟悉的清香味。\n"; break;
    		case 1: msg = "$N低头嗅了一下"+name+"，扭过头去打了一个香香喷。\n"; break;
    		case 2: msg = "$N捧着"+name+"一嗅，泪水滴在花瓣上。\n"; break;
    		case 3: msg = "$N将一朵"+name+"放在鼻子下，想啊想啊……\n"; break;
    		case 4: msg = "$N捧着"+name+"闻了一下：唉，今夕是何夕。\n"; break;
    		case 5: msg = "$N将"+name+"捧起闻了闻，又惦记起昨天的故人。\n"; break;
    		case 6: msg = "$N不禁将"+name+"轻轻一闻，思绪绵绵如窗外的细雨。\n"; break;
    		case 7: msg = "$N闻了闻"+name+"，痴痴地听着窗外飘过的小雨。\n"; break;
    		default : msg = "$N将"+name+"轻轻一嗅，不禁念道：明日天涯何处……\n"; break;
	}
  	message_vision (msg,me);
  	me->start_busy(1);
  	return 1;
}

int do_fix (string arg)
{
  	object me = this_player();
  	object flower = this_object();
  	string name = flower->query("name");
  	string msg;

  	if( !arg || !id(arg) || me!=environment() )
    		return 0;
    	if( query("fixed") )
    		return err_msg("已经包好了。\n");	
	msg = "$N将"+name+"小心地用湿润的丝绢包好。\n";
  	flower->set("fixed",1);
  	message_vision (msg,me);
  	return 1;
}

void heart_beat()
{
  	object who,flower = this_object();
  	string name = flower->query("name");
  	string msg;
  	object seed;
	if( !environment() )
		return;
  	who = environment();
  	if(!who || !living(who))
    		return;
	if(flower->query("fixed"))
    		return;
	switch (flower->query("water"))
  	{
    		case 0: msg = "风吹过，"+name+"在$N的眼前轻晃了一下。\n"; break;
    		case 1: msg = name+"有点干了，哦，该淋一点水了。\n"; break;
    		case 2: msg = name+"慢慢低下头。\n"; break;
    		case 3: msg = name+"抬起头，无声地看着$N。\n"; break;
    		case 4: msg = name+"艰难地重新伸直腰杆：“水”……\n"; break;
    		case 5: msg = name+"终于干枯了。\n"; flower->set("name","干"+name); break;
    		default:   //added by mon 8/31/97
      			msg = name+"看起来好难看。\n";
        		if( flower->query("water")>=10 && random(2)==0 ) 
        		{
          			message_vision(name+"随风而起，化作了片片花雨．．．
再看时，只有一粒乌黑的花籽还留在$N手上。\n",who);
	  			seed = new (__DIR__"seed");
	  			if( query("owner_id") )
	  				seed->set("owner_id",query("owner_id"));
          			seed->move(who);
          			destruct(flower);
	  			return;
			}
      			break;
  	}
  	if(msg)
  		message_vision (msg,who);
	add("water",1);
}

int do_water (string arg)
{
  	object flower = this_object();
  	object who = this_player();
  	string name = flower->query("name");
  	string msg;

  	if( !arg || !id(arg) )
    		return 0;
	if(flower->query("water") >= 5)
  	{
    		message_vision ("$N的泪水一滴滴流在"+name+"上。\n",who);
    		return 1;
  	}
	switch (random(9))
  	{
    		case 0: msg = "$N口含清水，喷在"+name+"的花瓣上。\n"; break;
    		case 1: msg = "$N将一点清水洒在"+name+"上。\n"; break;
    		case 2: msg = "$N伸出手抓住细细的小雨，淋在"+name+"上。\n"; break;
    		case 3: msg = "$N小心地捧起一点点露水，滴在"+name+"的花蕾上。\n"; break;
    		case 4: msg = "$N一阵心痛，泪水流在"+name+"的花瓣上。\n";break;
    		case 5: msg = "$N双手捧着"+name+"，伸到窗外的小雨中……\n";break;
    		case 6: msg = "$N仔细地拿起一只小杯子，将水滴在"+name+"上。\n";break;
    		case 7: msg = "$N捧起从野外采来的晨露，洒在"+name+"的花瓣上。\n";break;
    		default: msg = "$N用手指蘸着清水，一点点滴在"+name+"的花瓣上。\n";break;
	}
  	message_vision (msg,who);
  	message_vision (name+"重新露出了天真的笑容。\n",who);
  	flower->set("water",0);
  	return 1;
}
