// human.c

// A normal human is at least 35 kg weight
#define BASE_WEIGHT 35000

inherit F_DBASE;

mapping *combat_action = ({
        ([      "action":              "$N挥拳攻击$n的$l",
                "damage_type":  "瘀伤",
        ]),
        ([      "action":              "$N往$n的$l一抓",
                "damage_type":  "抓伤",
        ]),
        ([      "action":              "$N往$n的$l狠狠地踢了一脚",
                "damage_type":  "瘀伤",
        ]),
        ([      "action":              "$N提起拳头往$n的$l捶去",
                "damage_type":  "砸伤",
        ]),
        ([      "action":              "$N对准$n的$l用力挥出一拳",
                "damage_type":  "瘀伤",
        ]),
});

void create()
{
        seteuid(getuid());
}

void setup_human(object ob)
{
	mapping my,max;
    	int  qi, shen;

    	my = ob->query_entire_dbase();
        
    	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));
        
    	if( undefinedp(my["age"]) ) my["age"] = random(30) + 15;
	if( undefinedp(my["str"]) ) my["str"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["cor"]) ) my["cor"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["int"]) ) my["int"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["spi"]) ) my["spi"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["cps"]) ) my["cps"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["per"]) ) my["per"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["con"]) ) my["con"] = random(21) + 10+ob->query_level();
	if( undefinedp(my["kar"]) ) my["kar"] = random(21) + 10+ob->query_level();
	if( !userp(ob) && undefinedp(my["daoxing"]) )
		my["daoxing"] = ob->query_max_daoxing();
	
        if( userp(ob) || undefinedp(my["max_gin"]) || my["max_gin"]<1) 
        {
        	if( ob->query_level()<9 )
        		my["max_gin"] = 100;
        	else if( ob->query_level()<39 )
        		my["max_gin"] = 300;	
        	else	my["max_gin"] = ob->query_level()*20/3;	
        }
        
	qi = ob->query_con()*25+ob->query_str()+ob->query_level()*100;
	shen = ob->query_con()*25+ob->query_spi()+ob->query_level()*100;

	if( undefinedp(my["max_kee"]) || my["max_kee"]<qi )
		my["max_kee"] = qi;
	if( undefinedp(my["max_sen"]) || my["max_sen"]<shen )
		my["max_sen"] = shen;
		
	if(my["max_kee"]<1) my["max_kee"]=1;//mon 1/28/98
	if(my["max_sen"]<1) my["max_sen"]=1;//mon 1/28/98        
        if( undefinedp(my["unit"])) 
                my["unit"]="位";
        if( undefinedp(my["gender"])) 
                my["gender"]="男性";
        if( undefinedp(my["can_speak"])) 
                my["can_speak"]=1;
        if( undefinedp(my["attitude"])) 
                my["attitude"]="peaceful";
        if( undefinedp(my["limbs"])) 
                my["limbs"]=({
                        "头部", "颈部", "胸口", "后心", "左肩", "右肩", "左臂",
                        "右臂", "左手", "右手", "腰间", "小腹", "左腿", "右腿",
                        "左脚", "右脚"
                }) ;
	ob->powerup();
        if( !ob->query_weight() ) 
                ob->set_weight(BASE_WEIGHT + (my["str"] - 10)* 1000);
}

mapping query_action()
{
        return combat_action[random(sizeof(combat_action))];
}


