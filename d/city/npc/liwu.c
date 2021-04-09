#include <ansi.h>
inherit NPC;

string ask_for_pot()
{
        int pot;
        object me = this_player();
         if( me->query("giftmark/newbie2") )
                return 0;

      pot = 4500000;
        me->add("combat_exp",100000);
        me->add("daoxing",100000);
        me->add("potential",pot);
        tell_object(me,"你得到了10万武学经验、100年道行以及"+pot+"潜能。\n");
        me->set("giftmark/newbie2",1);  
        me->save();
        return "游戏快乐。";               
}

string ask_for_gold()
{
        int pot;
        object me = this_player();
        if( me->query("giftmark/newbie3") )
                return 0;
      
        me->money_add(500000);                
        tell_object(me,"你得到了50两黄金的新手资金。\n");
        me->set("giftmark/newbie3",1);  
        me->save();
        return "游戏快乐。";               
}

void create()
{
        set_name("破刀",({"po dao","po","dao"}));
        set("title",HIG"小雨接引使"NOR);
        set("long","新人接引使，你可以向他打听 新手礼物 和 新手资金的事，而且还可以通过yaowuqi来得到一把称手的武器。\n");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("str", 17);
        set("int", 30);
        set("spi", 30);
        set("con", 30);
        set("cps", 30);
        set("cor", 20);
        set("atman", 200);
        set("max_atman", 200);

        set("force", 120);
        set_skill("force",120);
        set("max_force", 150);
        set("force_factor", 5);

        set("mana", 200);
        set("max_mana", 200);

        set("combat_exp", 10000);
        set("daoxing", 50000);

        set("inquiry", ([
                "新手礼物" : (: ask_for_pot :),
                "gift" : (: ask_for_pot :),
                "新手资金" : (: ask_for_gold :),
                "gold" : (: ask_for_gold :),
                ]) );

        setup();
        carry_object("/d/obj/cloth/xianpao")->wear();
        add_temp("apply/karma",5000);
}

void init()
{
        add_action("do_yao","yaowuqi");
}

int do_yao(string arg)
{
       int i;
        string str,*file;
        object ob,me = this_player();
        if( !wizardp(me) && me->query("giftmark/newbie5") )
                return 0;
       
        file = ({
                "axe","blade","fork","hammer","mace",
                "spear","stick","staff","sword","whip",
                "unarmed",
        });
        if( !arg || member_array(arg,file)==-1 )
        {
                write("你可以要以下的武器：\n
        axe blade fork hammer mace spear stick staff sword whip unarmed
你只有一次机会，注意选择。\n");
                return 1;
        }
        
        ob=new("/d/obj/nweapon/"+arg);
        if( !ob )
                return 0;
        ob->set("no_give",1);
        ob->set("no_get",1);    
        ob->set("no_put",1);
        ob->set("no_zm",1);
        ob->set("no_steal",1);
        ob->init_weapon(this_object());

        if( ob->move(me) )
        {
                message_vision("$N将"+ob->name()+"交给$n，说道：小心保管，这宝贝下线、死亡都不会掉。\n",this_object(),me);
                tell_object(me,name()+"说道：想要更好的武器，就需要先去背阴巷打副本了，不过还要等等，巫师老忙啦。。。。 \n");
                me->set("giftmark/newbie5",1);
                me->save();
        }
        else    destruct(ob);
        return 1;
}
                
                                                
