// beast.c

#include <race/beast.h>

mapping combat_action =
([
	"hoof": ([
		"action":		"$N用後腿往$n的$l用力一蹬",
		"damage":		100,
		"damage_type":	"瘀伤",
	]),
	"bite": ([
		"action":		"$N扑上来张嘴往$n的$l狠狠地一咬",
		"damage":		20,
		"damage_type":	"咬伤",
	]),
	"claw": ([
		"action":		"$N用爪子往$n的$l一抓",
		"damage_type":	"抓伤",
	]),
	"poke": ([
		"action":		"$N用嘴往$n的$l一啄",
		"damage":		30,
		"damage_type":	"刺伤",
	]),
]);

string *actions;

void create()
{
	actions = keys(combat_action);
}

void setup_beast(object ob)
{
	mapping my,max;
	int  qi, shen;
	
	my = ob->query_entire_dbase();

	my["unit"] = "只";

	if( undefinedp(my["actions"]) ) {
		if( pointerp(my["verbs"]) )
			ob->set("default_actions", (: call_other, __FILE__, "query_action" :) );
		else	
			my["default_actions"] = ([
                                "action": ({"$N扑上来张嘴往$n的$l狠狠地一咬","$N用後腿往$n的$l用力一蹬","$N用爪子往$n的$l一抓",})[random(3)],
			]);
	}
	if( !userp(ob) && undefinedp(my["daoxing"]) )
		my["daoxing"] = ob->query_max_daoxing();
	if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
	if( undefinedp(my["age"]) ) my["age"] = random(40) + 5;

	if( undefinedp(my["str"]) ) my["str"] = random(41) + 20+ob->query_level();
	if( undefinedp(my["cor"]) ) my["cor"] = random(41) + 20+ob->query_level();
	if( undefinedp(my["int"]) ) my["int"] = 0;
	if( undefinedp(my["spi"]) ) my["spi"] = 0;
	if( undefinedp(my["cps"]) ) my["cps"] = random(11) + 20+ob->query_level();
	if( undefinedp(my["per"]) ) my["per"] = random(11) + 20+ob->query_level();
	if( undefinedp(my["con"]) ) my["con"] = random(41) + 20+ob->query_level();
	if( undefinedp(my["kar"]) ) my["kar"] = 0;

	if( undefinedp(my["max_gin"]) ) {
		if( my["age"] <= 3 ) my["max_gin"] = 50;
		else if( my["age"] <= 10 ) my["max_gin"] = 50 + (my["age"] - 3) * 20;
		else if( my["age"] <= 30 ) my["max_gin"] = 190 + (my["age"] - 10) * 5;
		else my["max_gin"] = my["max_gin"] = 290 + (my["age"] - 30);
	}
	qi = ob->query_con()*50+ob->query_str()+ob->query_level()*150;
	shen = ob->query_con()*50+ob->query_spi()+ob->query_level()*150;

	if( undefinedp(my["max_kee"]) || my["max_kee"]<qi )
		my["max_kee"] = qi;
	if( undefinedp(my["max_sen"]) || my["max_sen"]<shen )
		my["max_sen"] = shen;
		
	if(my["max_kee"]<1) my["max_kee"]=1;//mon 1/28/98
	if(my["max_sen"]<1) my["max_sen"]=1;//mon 1/28/98      
	//	NOTE: beast has no initial limbs defined, you must define it yourself.
	//	ob->init_limbs(LIMBS);
	ob->powerup();
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 2000);
}

mapping query_action(object me)
{
	string *act,str;
        act = me->query("verbs");
 	if(act)
 	{
 		if( str = act[random(sizeof(act))] )
 		{
 			if( !undefinedp(combat_action[str]) )
 				return combat_action[str];
 		}
	}
	return combat_action["bite"];
}
