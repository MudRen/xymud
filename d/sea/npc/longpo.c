inherit NPC;

void create()
{
       	set_name("龙婆", ({"long po"}));
       	set_level(100);
	set("long","龙王的老婆，东海的太后．\n");
       	set("gender", "女性");
       	set("age", 26);
	set_skill("parry",1000);
        set_skill("dodge",1000);
        set_skill("unarmed",1000);
	set_skill("dragonstep",1000);
	map_skill("dodge", "dragonstep");
	set("env/test",({"HIR","HIB"})[random(2)]);
	set_temp("weapon_level",40);
	set_temp("armor_level",40);
	setup();
        carry_object(0,"cloth",1)->wear();        
        carry_object(0,"neck",1)->wear();        
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"hand",1)->wear();
        carry_object(0,"waist",1)->wear();
        powerup(0,1);
}