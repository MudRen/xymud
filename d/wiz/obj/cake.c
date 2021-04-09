#include <ansi.h>
inherit ITEM; 

void init()
{
  	add_action("do_eat", "eat"); 
  	add_action("do_wish", "wish");
}

void create()
{
	string msg;
	set_name( HIY "生日蛋糕" NOR , ({"cake", "dangao"}));
  	set_weight(90);
  	if (clonep())
    		set_default_object(__FILE__);
  	else {
    		set("unit", "块");
    		if( random(2) )
			msg = @MSG
			
NORBLK                 ▂     ▂                    NOR
NORBLK               NORBLK▊NORHBWHT  NORBLK▎  NORHBWHTBLK▍ NORBLK▎      NOR
NORYEL               NORBLK▋NORHBWHT  NORHBWHTWHT NORBLK▎ NORHBWHTBLK▎NORWHT▋NOR
NORYEL               NORBLK▋NORHBWHT  NORWHT▊NORBLK▋NORHBWHT  NORHBWHTHIW NORBLK▎NOR
NORBLK               NORBLK▊NORHBWHTBLK_.-~~-._ NORBLK▍NOR
NORBLK             ◢NORHIR◢NORHBWHTHIR◣    ◢NORHIR◣NORBLK◣NOR
NORBLK             NORHIR◢NORHIR██NORHBWHTHIW●●NORHIR██NORHIR◣NOR
NORBLK           NORBLK▉ NORWHT▁▃▄▄▄▃NORBLK█ NOR
NORBLK          ◢NORWHT▅NORHBWHTBLK __--~~~~--__ NORWHT▅NORBLK◣NOR
NORBLK         NORHBWHTBLK▍ .-~            ~-.  NORBLK▍NOR
NORBLK       NORBLK▋NORHBWHTBLK  |                  |  NORBLK▍NOR
NORBLK      ▕NORHBWHTBLK▎  ~-._.---~~---._.-~   NORBLK▌NOR
NORBLK      NORBLK▊NORHBWHTBLK▏      ▁      ▁       NORWHT▊NORBLK▎NOR
NORBLK      NORBLK▊NORHBWHTBLK▎▁▄NORWHT▃▆NORHBWHTBLK      NORWHT▇▄NORHBWHTBLK▄▂ NORWHT▊NORBLK▏NORHIC    流氓兔公仔蛋糕，可以向他许愿(wish)NOR
NORBLK      ▁NORHBWHTBLK◣NORWHT▅NORHBWHTBLK                 NORWHT▇▅NORHBWHTBLK◢NORBLK▁__NOR HIC 要经验(exp)、潜能(pot)、道行(dx)。NOR
NORBLK  NORBLK▌NORWHT▆NORHBWHTHIR◥NORHIR◣ NORHBWHTBLK▄▂     ●   ,  ▁▃NORWHT NORHIR◢NORHBWHTHIR◤ NOR
NORHIW  NORHBWHTBLK▍NORHIR██NORHBWHTHIR◥NORBLK██ NORHBWHTBLK◣^-_  _--◢NORBLK▆NORBLK██NORHBWHTHIR◤NORHIR█NORHBWHTWHT█NORBLK▍NOR
NORBLK▌NORHBWHTWHT     NORHBWHTBLK▁ NORBLK︳██▆NORHBWHTBLK◣▔◢NORBLK▆█   ▁NORHBWHTBLK︳NORHBWHTWHT    NORWHT▌NOR
NORBLK  NORHBWHTBLK▍ NORWHT▊NORBLK▎NORHBWHTBLK▍NORBLK◣      ▆▆██  █NORWHT▋NORHBWHTBLK▎ NORHBWHTWHT█ NOR
NORBLK   NORHBWHTYEL NORHBWHTBLK▂NORBLK▏NORBLK▊NORHBWHTBLK▎NORWHT▇▆▄▃▃▃▄▅▇NORHBWHTBLK NORBLK▋ NORBLK▅▃▆NOR
NORBLK        ▕NORHBWHTBLK▍      NORHBWHTWHT            NORWHT▌NORHIW              NOR
NORBLK         NORHBWHTBLK▋                   NORWHT▋NORBLK▏  NORYEL          NOR
NORBLK NORYEL         NORHBWHTYEL NORHBWHTBLK◣     ▁▃▁     NORWHT◤NORBLK▎NOR
NORBLK           NORBLK◣▁▂▄▆▆▅▃▂◢NOR
MSG;
		else	msg = @MSG
		
NORBLK           ◢▇▆▄▂ ▂▄▆▇NORBLK◥NOR
NORBLK           NORHBWHTBLK◤     NORWHT▇▆▇NORHBWHTBLK      NORWHT◣NOR
NORBLK         NORBLK▊NORHBWHTBLK▎      NORHBWHTWHT           NORWHT▉NORBLK▍NOR
NORBLK     __  NORBLK▋NORHBWHTBLK                    NORBLK▍ ▂▁NOR
NORBLK NORBLK▋NORWHT▅▆NORBLK▍ NORHBWHTBLK▍  ▃▅▆NORWHT NORHBWHTBLK▇▆▅▃ NORWHT▊NORREVBLK NORHBWHTBLK▍ NORWHT▊NORBLK▏NOR
NORBLK NORHBWHTBLK▍NORHBYELHIR██NORHBWHTHIW NORBLK▍NORHBWHTYEL NORHBWHTHIW NORBLK   █      ███NORHBWHTBLK▊NORWHT▌NORHBWHTHIW NORHBYELHIR██NORBLK▍NOR
NORBLK▌NORHBWHTWHT      NORWHT▆NORHBWHTHIW NORBLK︳ ██NORHBWHTBLK◤__◥NORBLK████NORHBWHTBLK︳NORHBWHTWHT     NORBLK▎NOR
NORBLK▊NORHBYELHIR██NORHBWHTHIW   NORHBWHTHIR◢NORBLK █ NORWHT◢NORHBWHTBLK.-~  ~-.NORWHT◣NORBLK▁   NORHBWHTHIR◣   NORWHT▉NORBLK▏NOR
NORBLK  NORBLK NORHBWHTBLK▃▁NORHBWHTHIR◢NORHIR◤NORWHT▄▆NORHBWHTHIW     NORHBWHTBLK●   ` NORWHT▆▄ NORHIR◥NORHBWHTHIR◣NORHBWHTBLK▁NOR
NORBLK   NORBLK▇NORBLK NORBLK▆NORWHT◢NORHBWHTBLK▅▂               ▂▅◥NORBLK▆NOR
NORBLK      NORBLK▊NORHBWHTBLK▏  NORWHT▆▄NORHBWHTBLK▄       ▄NORWHT▄▆NORHBWHTBLK  NORWHT▊NORBLK▏NOR
NORBLK      NORBLK▊NORHBWHTBLK▏    __           __    ▕NORBLK▎NOR
NORBLK        NORHBWHTBLK▍ .-~  ~--.___.--~  ~-. NORWHT▋NOR      HIC流氓兔公仔蛋糕，可以向他许愿(wish)NOR
NORBLK       NORBLK▊NORHBWHTBLK▎︳                  |▕NORBLK▎NOR HIC    要经验(exp)、潜能(pot)、道行(dx)。NOR
NORBLK        NORBLK▋NORHBWHTBLK ~-._            _.-~  NORBLK▌ NOR  
NORBLK          ◥NORHBWHTBLK▂ ---.____.---  ▃NORBLK◤NOR
NORBLK              NORHBWHTBLK▆▄▃▃▃▄▆NOR
NORBLK             NORHIR◥NORHBYELHIR█NORHBYELHIR█NORHBWHTHIW●●NORHBYELHIR██NORHIR◤NOR
NORBLK             ◥NORHIR◥NORHBWHTHIR◤    ◥NORHIR◤NORBLK◤NOR
NORBLK               NORBLK▊NORHBWHTBLK~-.__.-~ NORBLK▎NOR
NORBLK               NORBLK▋NORHBWHT  NORWHT▊NORBLK▋NORHBWHTHIW  NORWHT▊NOR
NORBLK               NORBLK▋NORHBWHTHIW NORWHT▋NOR   NORHBWHTBLK▎ NORBLK▍NOR
NORBLK               NORBLK▊NORHBWHT  NORBLK▎ NORBLK▊NORHBWHT  NORBLK▏NOR
NORBLK                 NORHICBLK▆NOR     NORHICBLK▆NOR
MSG;	    		
		msg = COLOR_D->replace_color(msg,1);
		set("long", msg);
		set("value", 0);
    		set("no_beg",1);
    		set("no_get","蛋糕掉在地上就不能吃了！\n");
    		set("no_give","这是生日蛋糕啊，怎么能随便给人呢？\n");
    		set("no_drop","生日蛋糕扔了多可惜呀！\n");
    		set("no_put","生日蛋糕扔了多可惜呀！\n");
    		set("no_sell","这是定做的，卖不掉了。\n");
    		set("no_store","这是生日蛋糕啊，怎么能随便给人呢？\n");
    		set("no_steal",1);
  	}
  	setup();
}

int do_eat(string arg)
{
	object me, ob;
  	int vkar,gain;
   	me = this_player(); 
   	vkar=(int)me->query("kar");
   	
   	if( !arg || !id(arg) )
   		return 0;
	if( this_object()->query("onwerid")!=me->query("id") )
		return notify_fail("这个是你的蛋糕吗？\n");
	if( me->query("wished") )
      	{   
      		me->set("food", (int)me->max_food_capacity());
  		me->set("water", (int)me->max_water_capacity()); 
  		if( random(2) )
			write(HIG"你三口两口地把蛋糕吃了下去，打了个饱嗝。\n\n" NOR);  
		else	message_vision(HIG"$N"HIG"狼吞虎咽地把蛋糕吃了下去，意犹未尽地抹了抹嘴。\n"NOR, me); 	
		write(HIG"你的愿望实现啦！\n" NOR);  
		switch(me->query("wished"))
		{
			case "exp" : me->add("combat_exp",20000);break;
			case "pot" : me->add("potential",3000);break;
			default    : me->add("daoxing",5000);break;
		}
		me->delete("fired");
		me->delete("wished");
		destruct(this_object());
		return 1;
	}
	tell_object(me,HIM"吃蛋糕前先许个愿吧。可以许愿(wish)要经验(exp)、潜能(pot)、道行(dx)。\n"NOR);
	return 1;
} 
 
int do_wish(string arg) 
{
	object me = this_player();
	
	if( !arg || (arg!="exp" && arg!="pot" && arg!="dx") )
		return notify_fail("你要许什么愿？许愿要经验(exp)、潜能(pot)、道行(dx)\n");
	message_vision(HIY "$N闭上眼睛，默默地许了个愿。\n" NOR, me);  
	me->set("wished",arg);
    	return 1;
}