#include <ansi.h>
inherit COMBINED_ITEM;

void setup(){}

void create()
{
	set_name("木精",({"mu jing","jing",}));
    	set("changed",1);
    	if(clonep())
        	set_default_object(__FILE__);
    	else 
    	{
        	set("unit","些");
        	set("base_unit","块");
        	set("long","产自昆仑之地"HIG"建木遗迹"NOR"的一块木精，常被作为"HIC"筑基"NOR"五行材料。\n");
        	set("value",0);
        	set("base_weight",1000);
	}
        setup();
        set_amount(1);
}

int is_zhuji(){ return 1; }

void leave()
{
	remove_call_out("leave");
	if( environment() )
	{
		if( environment()->is_character() )
		{
			message("vision","\n\n”还我宝贝来！“半空忽然现出一只青色巨手，抓起"+environment()->name()+"身上的"+name()+"，青光一闪，顿时消失不见。\n\n",environment(environment()),environment());
			tell_object(environment(),"\n”还我宝贝来！“半空忽然现出一只青色巨手，一把将"+name()+"抓起，你眼前一花，已消失不见了！\n\n");
		}
		destruct(this_object());
	}
}

void init()
{
	if( environment() && environment()->is_character() 
	 && userp(environment()) )
	{
		if( query("owner_id") )
		{
			if( environment()->query("id")!=query("owner_id") )
			{
				remove_call_out("leave");
				call_out("leave",3);
				return;
			}
		}
		else	set("owner_id",environment()->query("id"));
	}	
}
