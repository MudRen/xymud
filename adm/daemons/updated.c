// updated.c
#include <ansi.h>

void create() { seteuid(getuid()); }

void check_user(object ob, int reconnect)
{
	int week,v1, v2,life;
	string m;
	mapping my;
	mixed *local;
	mapping colors;
    	string key;
    	int i,j,k;

	if( ob->query_life()==-1 )
	{
        	ob->announce_live_forever(ob->query("name")+"的道行达到了不堕轮回的境界，从此跳出三界外，不在五行中，永无生死大限了！");    
        }
        else
        {
        	life = ob->query_life();
        	if( !ob->query("life/init_life_time") )
        	{
        		ob->set("life/init_life_time", life);
        		ob->set("life/life_time", life);
        	}
        	else if( ob->query("life/init_life_time")>=life )
        		;
        	else
        	{
        		k = life-ob->query("life/init_life_time");
        		ob->set("life/init_life_time", life);
        		ob->add("life/life_time",k);
        	}	
	}
	ob->update_age();
	if( ob->check_gameover() ) return; 
	
	local = localtime(time());      
	week = local[6];
	if( !ob->query("mark/last_gin_full")
	  || ob->query("mark/last_gin_full")!=week )
	{
		ob->set("mark/last_gin_full",week);
		ob->set("gin",ob->query_maxgin());
		tell_object(ob,HIG"【系统】你的活力恢复了。\n"NOR);	  
	}
	
	ob->set("no_magic", 1);
	my = ob->query_entire_dbase();
	if( undefinedp(my["gin"]) ) my["gin"] = ob->query_maxgin();
	if( undefinedp(my["eff_kee"]) ) my["eff_kee"] = ob->query_maxkee();
	if( undefinedp(my["eff_sen"]) ) my["eff_sen"] = ob->query_maxsen();
	if( undefinedp(my["force"]) ) my["force"] = ob->query_maxforce();
	if( undefinedp(my["mana"]) ) my["mana"] = ob->query_maxmana();

	
	if( my["gin"] > ob->query_maxgin() ) my["gin"] = ob->query_maxgin();
	if( my["eff_kee"] > ob->query_maxkee() ) my["eff_kee"] = ob->query_maxkee();
	if( my["eff_sen"] > ob->query_maxsen() ) my["eff_sen"] = ob->query_maxsen();
	if( my["force"] > ob->query_maxforce()*2 ) my["force"] = ob->query_maxforce()*2;
	if( my["mana"] > ob->query_maxmana()*2 ) my["mana"] = ob->query_maxmana()*2;
				
	if( my["kee"] > my["eff_kee"] ) my["kee"] = my["eff_kee"];
	if( my["sen"] > my["eff_sen"] ) my["sen"] = my["eff_sen"];
	
	ob->stop_yinshen();
	if(  !wizardp(ob) && ob->query("env/immortal") )
		ob->delete("env/immortal");

	if(reconnect) return;

	colors=ob->query("quest/colors");
    	j=sizeof(colors);
    	if(j>1) 
    	{
       		for(i=0;i<j/2;i++) 
       		{
         		k=random(sizeof(colors));
         		key=keys(colors)[k];
         		map_delete(colors,key);
       		}
       		ob->set("quest/colors",colors);
    	}
	ob->update_title();
	if( ob->query_level()<30 )
		GIFT_D->update_level(ob);
	
}