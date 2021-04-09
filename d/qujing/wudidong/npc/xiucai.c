// xiucai.c 

inherit NPC;
 
void create()
{
        set_name("张及第", ({ "xiucai", "zhang jidi", "zhang" }));
        set_level(14);
        set("long", "张秀才是村里唯一会读书的。为考状元及第改了名，到头来还是个穷秀才。\n");
        set("title", "秀才");
        set("gender", "男性");
        set("age", 65);
 
        set_skill("literate", 140);
 
        set_skill("unarmed", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
 
        set("shen_type", 1);
        setup();
 
        set("chat_chance", 6);
        set("chat_msg", ({
                "张秀才说道：老夫写诗，别出心裁，不拘一格。就可惜没人能懂。唉。。。\n",
                "张秀才说道：早知道教书辛苦，不如算卦骗钱了。\n",
                "张秀才说道：之乎者也，之乎者也。汝若知乎，吾即折也。 \n",
                "张秀才说道：老夫胸怀安邦定国之策，至少也该请我到县衙门当个师爷呀！\n",
        }) );
}
 