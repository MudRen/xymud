#include <combat.h>
#include <ansi.h>

inherit __DIR__"n.c";

mapping style1= ([
	"action":               HIY"$N发出一声厉叫，手中$w"HIY"以一招"HIG"「六丁开山」"HIY"，带着呼呼风声向$n的$l砸去"NOR,                
	"dodge":                -5,
    "parry":             -15,
    "damage":               70,
    "damage_type":       "砸伤"                
]);
mapping style2= ([
	"action":               HIY"$N舞动$w"HIY"，使出"HIG"「八方风雨」"HIY"，幻出了无数$w向$n砸去"NOR,
    "dodge":                -15,
    "parry":            -10,                "damage":               40,
    "damage_type":   "砸伤"                
]);
mapping style3= ([
	"action":               HIY"$N舞动$w"HIY"，一式"HIG"「翻江搅海」"HIY"，劈头盖脸的向$n的$l砸去"NOR,                
	"dodge":                -5,
    "parry":             -30,
    "damage":               100,
    "damage_type":      "砸伤"                
]);
mapping style4= ([
	"action":               HIY"$N身形一转，一招"HIG"「飞砂走石」"HIY"使出，周围丈内土石乱飞，$w狠狠"HIY"已砸向$n的$l",                
	"dodge":                -25,
    "parry":            -30,
    "damage":               80,
    "damage_type":       "砸伤"                
]);
mapping style5= ([
	"action":               HIY"$N一招"HIG"「混沌初破」"HIY"使出，霹雳间$w"HIY"已砸向$n的$l，躲也躲不开了",                
	"dodge":                -35,
    "parry":            -40,
    "damage":               90,
    "damage_type":       "砸伤"                
]);
mapping style6= ([
	"action":               HIG"$N仰天长啸，看也不看，一招"HIY"「魔王回首」"HIG"，闪电霹雳般一棒向$n当头砸下"NOR,                
	"dodge":                -50,
    "parry":            -60,
    "damage":               100,
    "force":                    160,                
    "damage_type":      "砸伤"                
]);	

void create()
{
set_name("黄飞虎", ({"huang feihu", "huang", "feihu", "huangfeihu"}));
set ("long", @LONG
开国武成王黄飞虎，兴周第一大将，封神榜
上五岳之首东岳泰山大齐仁圣大帝，下凡寻
找其五色神牛的下落。
LONG);
set("title", "东岳泰山大齐仁圣大帝");
set("gender", "男性");
set("age", 43);
set_skill("spear", 450);
set_skill("force", 450);
set_skill("dodge", 450);
set_skill("stick", 450);
set_skill("literate", 450);
set_skill("dali-bang", 450);
set_skill("huoyun-qiang", 450);
set_skill("parry", 450);
set_skill("unarmed", 450);
set_skill("wuyue-spear", 450);
set_skill("spells", 450);
set_skill("pingtian-dafa", 450);
set_skill("moshenbu", 450);
set_skill("huomoforce", 450);
set_skill("moyun-shou", 450);
map_skill("force", "huomoforce");
map_skill("spells", "pingtian-dafa");
map_skill("unarmed", "moyun-shou");
map_skill("spear", "wuyue-spear");
map_skill("parry", "wuyue-spear");
map_skill("stick", "dali-bang");
map_skill("dodge", "moshenbu");
create_family("火云洞", 1, "蓝");
setup();
}

int is_boss() { return 1;}
void setup()
{
	int i;
	::setup();      
	set("combat_exp", 18225000);
	set("daoxing", 18225000);
	i = 4000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"spear",1)->wield();	
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object weapon;
	string msg;
	int d,k;
	this_object()->stop_busy();	
	remove_call_out("tiaozhan_hit");	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( !query_temp("shenli") && random(4)==2 )
	{
		message_vision(HIR"$N"HIR"哞的一声吼，一提丹田气，运力于臂，枪上加力。只见$P四周烈火重重，火焰像一条巨龙一样蜿蜒在枪上,如此的气势吓的敌手心惊丹寒\n" NOR,this_object());
		d = query_skill("spear")/5;
 		add_temp("apply/attack", d);  
        add_temp("apply/strength",d);    
        set_temp("shenli", 1);
    }
	if( random(5)==0 )
	{
		weapon = query_temp("weapon");
		if( !weapon )
		{
			msg = HIR"\n$N"HIR"大喝一声“掌心雷”！\n"NOR;
			set_temp("moyunshou_per", 6);
			set_temp("pfm_msg",1);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM,msg);
			delete_temp("moyunshou_per");
			delete_temp("pfm_msg");
		}
		else if( random(2) )
		{
			message_vision(HIR"\n只见$N"HIR"向"+weapon->query("name")+HIR"上吐了口鲜血,大喝一声:祭枪！\n"NOR,this_object());
			msg = HIR"但见$w"HIR"上忽地燃起一团诡异的火焰，焰光招摇之中，仿佛有道长影在黑暗中划过！只见摇熠的火光之中，窜出一道枪影，如毒蛇吐信般朝$n"HIR"$l刺去！\n"NOR;
			COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
		}
		else if( random(2) )
		{
	        msg = HIR"$N"HIR"手中$w"HIR"枪尖突然像着火一般，“砰”地炸出一团紫红色的火焰，绕着通红透亮的枪身燃烧起来！！“刷”地拉出一道火红中映着紫焰的流光，哗啦啦地就是一片遮天的火舌，往$n"HIR"的$l盖去！\n"NOR;
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
        
        	msg = HIR"\n$N"HIR"全身真气外放，衣衫冉冉飘动，双眸倏转妖红！！\n" NOR;
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);

			msg = HIC"\n$N"HIC"手中$w"HIC"内所有阳气已是内燃敛收，放出肉眼难以直视的青白光华！\n" NOR;
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM,msg);
		}
		else if( random(2) )
		{
			message_vision(HIC"$N"HIC"手中"+weapon->name()+HIC"倒提，枪作棍使，如暴风骤雨一般！\n"NOR,this_object());
			message_vision(HIG"\n$N"HIG"侧走一步，转身仰天咆哮，举棒力劈数招。！\n"NOR,this_object());
 			set("actions",style1);
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM);
 			set("actions",style2);
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM);
 			set("actions",style3);
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM);
 			set("actions",style4);
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM);
 			set("actions",style5);
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM);
 			set("actions",style6);
        	COMBAT_D->do_attack(this_object(),who,weapon,TYPE_PERFORM);
        	reset_action();
		}
	}
	else if( random(2) )
		QUEST_D->randomPfm(this_object());
	else
		command("cast niushi");	
	call_out("tiaozhan_hit",5,who);
}