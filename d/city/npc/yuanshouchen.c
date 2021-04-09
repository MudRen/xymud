#include <ansi.h>
inherit NPC;

string ask_mieyao();
string ask_cancel();

void create()
{
        set_name("袁守诚", ({"yuan shoucheng","yuan"}));
        set("title","算命先生");
        set_level(30);
        set("gender", "男性" );
        set("age", 55);
        set("class","taoist");
        set("long", "能知天地理，善晓鬼神情．长安城里没有不认识他的。\n");
        set("combat_exp", 800000000);
        set("daoxing", 80000000);

        set("attitude", "peaceful");
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set_skill("literate", 250);
        set_skill("scratmancy", 260);
        set_skill("spells", 250);
        set_skill("five-avoid", 250);
        set_skill("yinyang-zhang", 250);
        set_skill("wuzheng-force", 260);
        set_skill("zhanbu", 200);
        set_skill("blade", 250);
        set_skill("pomo-blade", 250);
        
        set("per", 15);
   	set("max_kee", 350000);
        set("max_gin", 300000);
        set("max_sen", 300000);
        set("max_mana", 200000);
        set("mana", 200000);
        set("mana_factor", 1000);
        set("chat_msg", ({
            "袁守诚晃了晃手上的桂花酒袋笑道：我这人没别的毛病，就是好点这个。\n",       
                "袁守诚上上下下打量了你几眼。\n",
                "袁守诚皱了皱眉，一副欲言又止的样子。\n",
                "袁守诚神秘兮兮地四面张望了一下，在你耳边悄声道：\n客官最近没觉得哪儿不得劲？\n",
        }) );
        setup();
	carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"sword",random(2))->wield();
}

int accept_object(object me, object ob)
{
        object nowords;
        
        if(userp(ob)) return 0;

        if( (string)ob->query("name")=="桂花酒袋" )
        {
                command("u&me " + me->query("id"));
                command("say 这位" + RANK_D->query_respect(me) + "就是跟我投缘！\n这里我也有一点小意思，请笑纳。\n");
                nowords = carry_object("/d/obj/book/nowords");
                if( nowords && nowords->move(me) )  tell_object(me,name()+"给你一"+nowords->query("unit")+nowords->name(1)+"。\n");
                else   tell_object(me,name()+"说道：你身上东西太多耶~~。\n");
                return 1;
        }
        return 0;
}