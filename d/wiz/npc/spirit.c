// by night
// fid 修改
#include <ansi.h>
#include <localtime.h>
inherit NPC; 

int ask_cake();

void create()
{
        set_name("精灵", ({ "spirit" }) );
        set("nickname", HIW "生辰" NOR);
        set("gender", "女性" );
        set_level(10);
	set("age", 20);
        set("long", "精灵楼的主人，管理着精灵楼的一切事务。\n" );
        set("attitude", "friendly");
      	set("shen_type", 1);
        set("class", "xian");
        set("per",60);
	set("inquiry", ([
		"生日礼物" : (: ask_cake :),      
	]));
        set("chat_chance",1);
      	set("chat_msg", ({
            "生辰精灵拿出一本"+HIW"《精灵物语》"NOR+"，专心地读了起来。\n", 
            "生辰精灵随着光芒一闪一闪，无聊地说：“怎么没人来领礼物呢？”\n",
            "生辰精灵笑嘻嘻地说：“要节日礼物，找我就对了。”\n",      }) );
        setup();
	carry_object(0,"cloth",1)->wear();
}

int ask_cake()
{ 
        object ob;
        if (this_player()->query("birthday_ask"))    
        {
        	command("say 恭喜恭喜，祝你生日快乐！\n");
        	ob=new("d/wiz/obj/cake");  //礼物的路径，自定义。
        	ob->set("onwerid",this_player()->query("id")); 
        	ob->move(this_player()); 
        	message_vision("\n$N给了$n一个特制的生日蛋糕。\n",  this_object(),this_player());
        	message("chat",HIC+"〖"+HIW+"小雨西游"+HIC+"〗生辰精灵：恭喜"+this_player()->query("name")+"得到了生日蛋糕！\n"NOR,users());
        	this_player()->delete("birthday_ask"); 
        	this_player()->save(1);
        	return 1;
        }
        message_vision("\n$N对$n说道：不是你的生日吧？\n",  this_object(),this_player());
      	return 1;
}
