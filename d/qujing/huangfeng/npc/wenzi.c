//Cracked by Roath
inherit NPC;

string *names = ({
  "[31mè±èèå­[m",
  "å¤§å¤´èå­",
  "ç´«å¤´èå­",
  "çº¢å¤´èå­",
  "è±è¾¹èå­",
  "è±èèå­",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({ "wen zi","wenzi" }) );
   set("race", "éå½");
   set("age", 3);
   set("long", "ä¸åªå¾å°å·§çè±èèå­ã\n");
   set_level(39);
   set("str", 32);
   set("limbs", ({ "å¤´é¨", "èº«ä½", "è¿", "ç¿è", "å´å·´" }) );
   set("verbs", ({ "bite", "claw" }) );
   set("chat_chance",80);
   set("chat_msg",({
        "èå­å¡å¡å¡çé£æ¥é£å»ã\n",
        }));
   set_temp("apply/attack", 10);
   setup();
}
