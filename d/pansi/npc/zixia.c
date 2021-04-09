//zixiaxianzi.c 2001 by lestat
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

void create()
{
        set_name(HIM"紫霞仙子"NOR, ({"zixia xianzi", "zixia", "xianzi","master"}));
        set("long", "她就是盘丝洞的开山祖师,传说她是佛祖的一棵灯芯。随佛祖修道悟
真,后来思凡下界占了花果山一处洞府,开山立派,传授门徒。\n");
        set("title", HIB"盘丝大仙"NOR);
        set("gender", "女性");
        set("age", 20);
        set_level(129);
        set("class","yaomo");
        set("attitude", "friendly");
        set("force_factor", 125);
        set("mana_factor", 250);
        set_skill("literate",1290);
        set_skill("unarmed", 1290);
        set_skill("dodge", 1290);
        set_skill("force",1290);
        set_skill("parry",1290);
        set_skill("spells", 1290);
        set_skill("whip", 1290);
        set_skill("pansi-dafa", 1290);
        set_skill("lanhua-shou",1290);
        set_skill("jiuyin-xinjing",1290);
        set_skill("yueying-wubu",1290);
        set_skill("yinsuo-jinling", 1290);
        map_skill("spells", "pansi-dafa");
        map_skill("unarmed", "lanhua-shou");
        map_skill("force", "jiuyin-xinjing");
        map_skill("parry", "yinsuo-jinling");
        map_skill("dodge", "yueying-wubu");
        map_skill("whip", "yinsuo-jinling");
        create_family("盘丝洞", 1, "红");
        set("env/test","HIB");
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"neck",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"whip",1)->wield();
//         carry_object("/d/pansi/obj/baohe.c");
}

void attempt_apprentice(object ob)
{
	if ( ob->query_level()<60 )
        {
        	command("say " + RANK_D->query_respect(ob) +"的道行不够高深，有些绝学秘法恐怕难以领悟。\n");
		return;
	}
	command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +"多加努力，他日帮我杀了那个臭猴子。\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

int accept_fight(object me) { return 0; }


void die()
{
	if( environment() )
		message("vision","\n\n火光一闪，"+this_object()->name()+"化作一道金光遁去。。。。\n\n",environment());	
        destruct(this_object());
}

string ask_pfm()
{
        object me = this_player();
        mapping skill = me->query_skills();
        if( me->query("family/family_name")
         && me->query("family/family_name")=="盘丝洞"  )
        {        
                //已问过的或解了的
                if( me->query_temp("pansi_pfm_ask") 
                 || me->query("pansi/zhenfa") )
                        return "不是叫你去帮我寻圣灵珠吗？";
                //纯skill，装备加的不算         
                if( !skill || skill["whip"]<100 )
                        return "你还不够资格。";
                me->set_temp("pansi_pfm_ask",1);
                return "将那圣灵珠寻来给我。";
        }
        else    return 0; //其他门派问不到
}

int accept_object(object who,object obj)
{
        int i;
        //没问过
        if( !who->query_temp("pansi_pfm_ask") )                 
                return 0;
        if( base_name(obj)=="/d/obj/baowu/shengzhu" )
        {
                command("smile");
                say(name()+"笑着说：这正是我想要的。\n"); //say函数相当于tell_room(environment())
                i = random(who->query_kar());
                if( i>12 && i<25 )
                {
                        tell_object(who,name()+"对了你点了点头，说道：好，我这就将「盘丝情花阵」的秘密说与你知。\n");
                        tell_object(who,HIR"你领悟了「盘丝情花阵」。\n"NOR);
                        CHANNEL_D->do_channel(this_object(),"rumor","听说"+who->name()+HIM"悟得了「"HIR"盘丝情花阵"HIM"」！"NOR);
                        who->set("pansi/zhenfa",1);
                        who->delete_temp("pansi_pfm_ask");
                        who->save();
                }
                else	say(name()+"不屑的瞅了你一眼：想要哄得我开心，就多给我寻些漂亮的圣灵珠子来。\n");
                return 1;
        }
        return 0;
}
