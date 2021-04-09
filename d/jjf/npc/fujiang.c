//created 8-3-97 pickle
//副将
inherit SUPER_NPC;

string weapon_file, skill, special_skill;
string *ns = ({"秦","罗","尉迟","程",});

void determine_data()
{
  switch(random(5))
    {
        case 0:
        {
	    weapon_file="sword";
	    skill="sword";
	    special_skill="xiaofeng-sword";
	    break;
        }
        case 1:
        {
	    weapon_file="blade";
	    skill="blade";
	    special_skill="wuhu-blade";
	    break;
        }
        case 2:
        {
	    weapon_file="mace";
	    skill="mace";
	    special_skill="wusi-mace";
	    break;
        }
        case 3:
        {
	    weapon_file="spear";
	    skill="spear";
	    special_skill="bawang-qiang";
	    break;
        }
        case 4:
        {
	    weapon_file="axe";
	    skill="axe";
	    special_skill="sanban-axe";
	    break;
        }
    }
}

void create()
{
	mapping name;
	int i;
    	name = NAME_D->random_name2(0, 1, ns[random(sizeof(ns))],0,"唐");
	set_name(name["name"],name["id"]);
  	i=10+random(20);
  	set_level(i);
  	set ("long", @LONG
他曾跟秦琼，程咬金，尉迟恭等人一齐在沙场上出生入死，靠着战功
一步步升到了副将。如今太平了，便练练兵，以防边疆有变。
LONG);
  	determine_data();
  	create_family("将军府",4,"");
  	set("title", "副将");
  	set("gender", "男性");
  	set("age", 20+random(30));
  	set_skill(skill,i*10);
	set_skill("dodge",i*10);
	set_skill("parry",i*10);
	set_skill("unarmed",i*10);
	set_skill("force",i*10);
	set_skill("changquan",i*10);
	set_skill(special_skill,i*10);
	set_skill("lengquan-force",i*10);
	set_skill("yanxing-steps",i*10);
  	map_skill(skill, special_skill);
  	map_skill("unarmed", "changquan");
  	map_skill("dodge", "yanxing-steps");
  	map_skill("parry", special_skill);
	set("force_factor", 25);
	setup();
 	carry_object(0,weapon_file,random(2))->wield();
  	carry_object(0,"armor",random(4))->wear();
}

