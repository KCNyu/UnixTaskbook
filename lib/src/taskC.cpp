#include "taskC.hpp"

TaskC::TaskC()
{
    library_name = "libtaskC.so";

    complier = "gcc";

    complie_argv = {complier, "-Wall", "", "-o"};

    task_count = 16;

    total_test_count = 3;

    task_text_russian = {
        "Дана строка S (не содержащая пробелов) и текстовый файл. Добавить строку S в конец файла.",
        "Даны два текстовых файла. Добавить в конец первого файла содержимое второго файла.",
        "Дана строка S (не содержащая пробелов) и текстовый файл. Добавить строку S в начало файла.",
        "Даны два текстовых файла. Добавить в начало первого файла содержимое второго файла.",
        "Дано целое число K и текстовый файл. Вставить пустую строку перед строкой файла с номером K (строки нумеруются от 1). Если строки с таким номером нет, то оставить файл без изменений.",
        "Дано целое число K и текстовый файл. Вставить пустую строку после строки файла с номером K (строки нумеруются от 1). Если строки с таким номером нет, то оставить файл без изменений.",
        "Дан текстовый файл. Продублировать в нем все пустые строки.",
        "Дана строка S (не содержащая пробелов) и текстовый файл. Заменить в файле все пустые строки на строку S.",
        "Дан непустой текстовый файл. Удалить из него первую строку.",
        "Дан непустой текстовый файл. Удалить из него последнюю строку.",
        "Дано целое число K и текстовый файл. Удалить из файла строку с номером K (строки нумеруются от 1). Если строки с таким номером нет, то оставить файл без изменений.",
        "Дан текстовый файл. Удалить из него все пустые строки.",
        "Даны два текстовых файла. Добавить в конец каждой строки первого файла соответствующую строку второго файла. Если второй файл короче первого, то оставшиеся строки первого файла не изменять.",
        "Дано целое числоKи текстовый файл. Удалить из каждой строки файла первые K символов (если длина строки меньше K, то удалить из нее все символы).",
        "Дано целое числоKи текстовый файл. Удалить из каждой строки файла последние K символов (если длина строки меньше K, то удалить из нее все символы).",
        "Дан текстовый файл. Заменить в нем все прописные буквы на строчные, а все строчные — на прописные. Остальные символы не изменять."};
    task_text_chinese = {
        "给定一个字符串 S（不包含空格）和一个文本文件。 将第 S 行添加到文件末尾。",
        "给出了两个文本文件。 将第二个文件的内容附加到第一个文件的末尾。",
        "给定一个字符串 S（不包含空格）和一个文本文件。 将第 S 行添加到文件的开头。",
        "给出了两个文本文件。 将第二个文件的内容添加到第一个文件的开头。",
        "给定一个整数 K 和一个文本文件。 在文件编号为 K 的行之前插入一个空行（行从 1 开始编号）。 如果没有带有此编号的行，则保持文件不变。",
        "给定一个整数 K 和一个文本文件。 在文件中的行号 K 之后插入一个空行（行从 1 开始编号）。 如果没有带有此编号的行，则保持文件不变。",
        "给定一个文本文件。 复制其中的所有空行。",
        "给定一个字符串 S（不包含空格）和一个文本文件。 用字符串 S 替换文件中的所有空行。",
        "给定一个非空的文本文件。 从中删除第一行。",
        "给定一个非空的文本文件。 从中删除最后一行。",
        "给定一个整数 K 和一个文本文件。 从文件中删除编号为 K 的行（行从 1 开始编号）。 如果没有带有此编号的行，则保持文件不变。",
        "给定一个文本文件。 从中删除所有空行。",
        "给出了两个文本文件。 将第二个文件的对应行追加到第一个文件的每一行末尾。 如果第二个文件比第一个文件短，则不要更改第一个文件的其余行。",
        "给定一个整数和一个文本文件。 从文件的每一行中删除前 K 个字符（如果该行的长度小于 K，则从中删除所有字符）。",
        "给定一个整数和一个文本文件。 从文件的每一行中删除最后 K 个字符（如果该行的长度小于 K，则从中删除所有字符）。",
        "给定一个文本文件。 将其中的所有大写字母替换为小写字母，并将所有小写字母替换为大写字母。 不要改变其余的字符。"};

    text_data = {"Winnie-the-Pooh sat down at the foot of the tree,\nput his head between his paws and began to think.\n\nFirst of all he said to himself: \"That\nbuzzing-noise means something. You don't get a\nbuzzing-noise like that, just buzzing and buzzing,\nwithout its meaning something. If there's a\nbuzzing-noise, somebody's making a buzzing-noise,\nand the only reason for making a buzzing-noise\nthat I know of is because you're a bee.\"\n\nThen he thought another long time, and said: \"And\nthe only reason for being a bee that I know of is\nmaking honey.\"\n\nAnd then he got up, and said: \"And the only reason\nfor making honey is so as I can eat it.\" So he\nbegan to climb the tree.\n",
                 "\"Oh, help!\" said Pooh, as he dropped ten feet on\nthe branch below him.\n\n\"If only I hadn't -\" he said, as he bounced twenty\nfeet on to the next branch.\n\n\"You see, what I meant to do,\" he explained, as he\nturned head-over-heels, and crashed on to another\nbranch thirty feet below, \"what I meant to do -\"\n\n\"Of course, it was rather -\" he admitted, as he\nslithered very quickly through the next six\nbranches.\n\n\"It all comes, I suppose,\" he decided, as he said\ngood-bye to the last branch, spun round three\ntimes, and flew gracefully into a gorse-bush, \"it\nall comes of liking honey so much. Oh, help!\"\n",
                 "\"Christopher Robin, you must shoot the balloon\nwith your gun. Have you got your gun?\"\n\n\"Of course I have,\" you said. \"But if I do that,\nit will spoil the balloon,\" you said.\n\n\"But if you don't,\" said Pooh, \"I shall have to\nlet go, and that would spoil me.\"\n\nWhen he put it like this, you saw how it was, and\nyou aimed very carefully at the balloon, and\nfired.\n\n\"Ow!\" said Pooh.\n\n\"Did I miss?\" you asked.\n\n\"You didn't exactly miss,\" said Pooh, \"but you\nmissed the balloon.\"\n",
                 "Pooh always liked a little something at eleven\no'clock in the morning, and he was very glad to\nsee Rabbit getting out the plates and mugs; and\nwhen Rabbit said, \"Honey or condensed milk with\nyour bread?\" he was so excited that he said,\n\"Both,\" and then, so as not to seem greedy, he\nadded, \"But don't bother about the bread, please.\"\nAnd for a long time after that he said nothing...\nuntil at last, humming to himself in a rather\nsticky voice, he got up, shook Rabbit lovingly by\nthe paw, and said that he must be going on.\n",
                 "\"Must you?\" said Rabbit politely.\n\n\"Well,\" said Pooh, \"I could stay a little longer\nif it - if you -\" and he tried very hard to look\nin the direction of the larder.\n\n\"As a matter of fact,\" said Rabbit, \"I was going\nout myself directly.\"\n\n\"Oh, well, then, I'll be going on. Good-bye.\"\n\n\"Well, good-bye, if you're sure you won't have any\nmore.\"\n\n\"Is there any more?\" asked Pooh quickly.\n\nRabbit took the covers off the dishes, and said,\n\"No, there wasn't.\"\n\n\"I thought not,\" said Pooh, nodding to himself.\n\"Well, good-bye. I must be going on.\"\n",
                 "The Piglet lived in a very grand house in the\nmiddle of a beech-tree, and the beech-tree was in\nthe middle of the forest, and the Piglet lived in\nthe middle of the house. Next to his house was a\npiece of broken board which had: \"TRESPASSERS W\"\non it. When Christopher Robin asked the Piglet\nwhat it meant, he said it was his grandfather's\nname, and had been in the family for a long time.\nChristopher Robin said you couldn't be called\nTrespassers W, and Piglet said yes, you could,\nbecause his grandfather was, and it was short for\nTrespassers Will, which was short for Trespassers\nWilliam. And his grandfather had had two names in\ncase he lost one - Trespassers after an uncle, and\nWilliam after Trespassers.\n",
                 "\"It's a very funny thing,\" said Bear, \"but there\nseem to be two animals now. This - whatever-it-was\n- has been joined by another - whatever-it-is -\nand the two of them are now proceeding in company.\nWould you mind coming with me, Piglet, in case\nthey turn out to be Hostile Animals?\"\n\nPiglet scratched his ear in a nice sort of way,\nand said that he had nothing to do until Friday,\nand would be delighted to come, in case it really\nwas a Woozle.\n\n\"You mean, in case it really is two Woozles,\" said\nWinnie-the-Pooh, and Piglet said that anyhow he\nhad nothing to do until Friday.\n",
                 "The Old Grey Donkey, Eeyore, stood by himself in a\nthistly corner of the forest, his front feet well\napart, his head on one side, and thought about\nthings. Sometimes he thought sadly to himself,\n\"Why?\" and sometimes he thought, \"Wherefore?\" and\nsometimes he thought, \"Inasmuch as which?\" - and\nsometimes he didn't quite know what he was\nthinking about. So when Winnie-the-Pooh came\nstumping along, Eeyore was very glad to be able to\nstop thinking for a little, in order to say \"How\ndo you do?\" in a gloomy manner to him.\n",
                 "So Eeyore stood there, gazing sadly at the ground,\nand Winnie-the-Pooh walked all round him once.\n\n\"Why, what's happened to your tail?\" he said in\nsurprise.\n\n\"What has happened to it?\" said Eeyore.\n\n\"It isn't there!\"\n\n\"Are you sure?\"\n\n\"Well, either a tail is there or it isn't there\nYou can't make a mistake about it. And yours isn't\nthere!\"\n\n\"Then what is?\"\n\n\"Nothing.\"\n",
                 "Owl lived at The Chestnuts, and old-world\nresidence of great charm, which was grander than\nanybody else's, or seemed so to Bear, because it\nhad both a knocker and a bell-pull. Underneath the\nknocker there was a notice which said:\n\nPLES RING IF AN RNSER IS REQIRD.\n\nUnderneath the bell-pull there was a notice which\nsaid:\n\nPLEZ CNOKE IF AN RNSR IS NOT REQID.\n\nThese notices had been written by Christopher\nRobin, who was the only one in the forest who\ncould spell; for Owl, wise though he was in many\nways, able to read and write and spell his own\nname WOL, yet somehow went all to pieces over\ndelicate words like MEASLES AND BUTTEREDTOAST.\n",
                 "\"Owl! I require an answer! It's Bear speaking.\"\nAnd the door opened, and Owl looked out.\n\n\"Hallo, Pooh,\" he said. \"How's things?\"\n\n\"Terrible and Sad,\" said Pooh, \"because Eeyore,\nwho is a friend of mine, has lost his tail. And\nhe's Moping about it. So could you very kindly\ntell me how to find it for him?\"\n\n\"Well,\" said Owl, \"the customary procedure in such\ncases is as follows.\"\n\n\"What does Crustimoney Proseedcake mean?\" said\nPooh. \"For I am a Bear of Very Little Brain, and\nlong words Bother me.\"\n",
                 "\"It was he who wrote the ones on my front door for\nme. Did you see them, Pooh?\"\n\nFor some time now Pooh had been saying \"Yes\" and\n\"No\" in turn, with his eyes shut, to all that Owl\nwas saying, and having said, \"Yes, yes,\" last\ntime, he said \"No, not at all,\" now, without\nreally knowing what Owl was talking about.\n\n\"Didn't you see them?\" said Owl, a little\nsurprised. \"Come and look at them now.\"\n\nSo they went outside. And Pooh looked at the\nknocker and the notice below it, and he looked at\nthe bell-rope and the notice below it, and the\nmore he looked at the bell-rope, the more he felt\nthat he had seen something like it, somewhere\nelse, sometime before.\n",
                 "At first as they stumped along the path which\nedged the Hundred Acre Wood, they didn't say much\nto each other; but when they came to the stream,\nand had helped each other across the stepping\nstones, and were able to walk side by side again\nover the heather, they began to talk in a friendly\nway about this and that, and Piglet said, \"If you\nsee what I mean, Pooh,\" and Pooh said, \"It's just\nwhat I think myself, Piglet,\" and Piglet said,\n\"But, on the other hand, Pooh, we must remember,\"\nand Pooh said, \"Quite true, Piglet, although I had\nforgotten it for the moment.\"\n",
                 "\"Suppose,\" he said to Piglet, \"you wanted to catch\nme, how would you do it?\"\n\n\"Well,\" said Piglet, \"I should do it like this. I\nshould make a Trap, and I should put a Jar of\nHoney in the Trap, and you would smell it, and you\nwould go in after it, and -\"\n\n\"And I would go in after it,\" said Pooh excitedly,\n\"only very carefully so as not to hurt myself, and\nI would get to the Jar of Honey, and I should lick\nround the edges first of all, pretending that\nthere wasn't any more, you know, and then I should\nwalk away and think about it a little, and then I\nshould come back and start licking in the middle\nof the jar, and then -\"\n\n\"Yes, well never mind about that. There you would\nbe, and there I should catch you.'\n",
                 "Eeyore, the old grey Donkey, stood by the side of\nthe stream, and looked at himself in the water.\n\n\"Pathetic,\" he said. \"That's what it is.\nPathetic.\"\n\nHe turned and walked slowly down the stream for\ntwenty yards, splashed across it, and walked\nslowly back on the other side. Then he looked at\nhimself in the water again.\n\n\"As I thought,\" he said. \"No better from this\nside. But nobody minds. Nobody cares. Pathetic,\nthat's what it is.\"\n",
                 "\"Well, that's funny,\" he thought. \"I wonder what\nthat bang was. I couldn't have made such a noise\njust falling down. And where's my balloon? And\nwhat's that small piece of damp rag doing?\"\n\nIt was the balloon!\n\n\"Oh, dear!\" said Piglet. \"Oh, dear, oh, dearie,\ndearie, dear! Well, it's too late now. I can't go\nback, and I haven't another balloon, and perhaps\nEeyore doesn't like balloons so very much.\"\n",
                 "\"The best way,\" said Rabbit, \"would be this. The\nbest way would be to steal Baby Roo and hide him,\nand then when Kanga says, \"Where's Baby Roo?\" we\nsay, \"Aha!\"\"\n\n\"Aha!\" said Pooh, practising. \"Aha! Aha!... Of\ncourse,\" he went on, \"we could say \"Aha!\" even if\nwe hadn't stolen Baby Roo.\"\n\n\"Pooh,\" said Rabbit kindly, \"you haven't any\nbrain.\"\n\n\"I know,\" said Pooh humbly.\n",
                 "\"There's just one thing,\" said Piglet, fidgeting a\nbit. \"I was talking to Christopher Robin, and he\nsaid that a Kanga was Generally Regarded as One of\nthe Fiercer Animals. I am not frightened of Fierce\nAnimals in the ordinary way, but it is well known\nthat, if One of the Fiercer Animals is Deprived of\nIts Young, it becomes as fierce as Two of the\nFiercer Animals. In which case \"Aha!\" is perhaps a\nfoolish thing to say.\"\n\n\"Piglet,\" said Rabbit, taking out a pencil, and\nlicking the end of it, \"you haven't any pluck.\"\n\n\"It is hard to be brave,\" said Piglet, sniffing\nslightly, \"when you're only a Very Small Animal.\"\n",
                 "Pooh was just going to say \"Hallo!\" for the fourth\ntime when he thought that he wouldn't, so he said,\n\"Who is it?\" instead.\n\n\"Me,\" said a voice.\n\n\"Oh!\" said Pooh. \"Well, come here.\"\n\nSo Whatever-it-was came here, and in the light of\nthe candle he and Pooh looked at each other.\n\n\"I'm Pooh,\" said Pooh.\n\n\"I'm Tigger,\" said Tigger.\n",
                 "So he took a large mouthful, and he gave a large\ncrunch.\n\n\"Ow!\" said Tigger.\n\nHe sat down and put his paw in his mouth.\n\n\"What's the matter?\" asked Pooh.\n\n\"Hot!\" mumbled Tigger.\n\n\"Your friend,\" said Eeyore, \"appears to have\nbitten on a bee.\"\n\nPooh's friend stopped shaking his head to get the\nprickles out, and explained that Tiggers didn't\nlike thistles.\n\n\"Then why bend a perfectly good one?\" asked\nEeyore.\n",
                 "\"Are they stuck?\" asked Piglet anxiously.\n\nPooh nodded.\n\n\"Couldn't you climb up to them?\"\n\n\"I might, Piglet, and I might bring Roo down on my\nback, but I couldn't bring Tigger down. So we must\nthink of something else.\" And in a thoughtful way\nhe began to eat Roo's sandwiches, too.\n\nWhether he would have thought of anything before\nhe had finished the last sandwich, I don't know,\nbut he had just got to the last but one when there\nwas a crackling in the bracken, and Christopher\nRobin and Eeyore came strolling along together.\n",
                 "\"I thought,\" said Piglet earnestly, \"that if\nEeyore stood at the bottom of the tree, and if\nPooh stood on Eeyore's back, and if I stood on\nPooh's shoulders -\"\n\n\"And if Eeyore's back snapped suddenly, then we\ncould all laugh. Ha ha! Amusing in a quiet way,\"\nsaid Eeyore, \"but not really helpful.\"\n\n\"Well,\" said Piglet meekly, \"I thought -\"\n\n\"Would it break your back, Eeyore?\" asked Pooh,\nvery much surprised.\n\n\"That's what would be so interesting, Pooh. Not\nbeing quite sure till afterwards.\"\n\nPooh said \"Oh!\" and they all began to think again.\n",
                 "\"The fact is,\" said Rabbit, \"we've missed our way\nsomehow.\"\n\nThey were having a rest in a small sand-pit on the\ntop of the Forest. Pooh was getting rather tired\nof that sand-pit, and suspected it of following\nthem about, because whichever direction they\nstarted in, they always ended up at it, and each\ntime, as it came through the mist at them, Rabbit\nsaid triumphantly, \"now I know where we are!\" and\nPooh said sadly, \"So do I,\" and Piglet said\nnothing. He had tried to think of something to\nsay, but the only thing he could think of was,\n\"Help, help!\" and it seemed silly to say that,\nwhen he had Pooh and Rabbit with him.\n",
                 "\"How would it be?\" said Pooh slowly, \"if, as soon\nas we're out of sight of this Pit, we try to find\nit again?\"\n\n\"What's the good of that?\" said Rabbit.\n\n\"Well,\" said Pooh, \"we keep looking for Home and\nnot finding it, so I thought that if we looked for\nthis Pit, we'd be sure not to find it, which would\nbe a Good Thing, because then we might find\nsomething that we weren't looking for, which might\nbe just what we were looking for, really.\"\n\n\"I don't see much sense in that,\" said Rabbit.\n\n\"No,\" said Pooh humbly, \"there isn't. But there\nwas going to be when I began it. It's just that\nsomething happened to it on the way.\"\n",
                 "\"If I walked away from this Pit, and then walked\nback to it, of course I should find it.\"\n\n\"Well, I thought perhaps you wouldn't,\" said Pooh.\n\"I just thought.\"\n\n\"Try,\" said Piglet suddenly. \"We'll wait here for\nyou.\"\n\nRabbit gave a laugh to show how silly Piglet was,\nand walked into the mist. After he had gone a\nhundred yards, he turned and walked back again ...\nand after Pooh and Piglet had waited twenty\nminutes for him, Pooh got up.\n\n\"I just thought,\" said Pooh. \"Now then, Piglet,\nlet's go home.\"\n",
                 "\"Rabbit's clever,\" said Pooh thoughtfully.\n\n\"Yes,\" said Piglet, \"Rabbit's clever.\"\n\n\"And he has Brain.\"\n\n\"Yes,\" said Piglet, \"Rabbit has Brain.\"\n\nThere was a long silence.\n\n\"I suppose,\" said Pooh, \"that that's why he never\nunderstands anything.\"\n",
                 "\"Hallo, Eeyore,\" they called out cheerfully.\n\n\"Ah!\" said Eeyore. \"Lost your way?\"\n\n\"We just came to see you,\" said Piglet. \"And to\nsee how your house was. Look, Pooh, it's still\nstanding!\"\n\n\"I know,\" said Eeyore. \"Very odd. Somebody ought\nto have come down and pushed it over.\"\n\n\"We wondered whether the wind would blow it down,\"\nsaid Pooh.\n\n\"Ah, that's why nobody's bothered, I suppose. I\nthought perhaps they'd forgotten.\"\n",
                 "The wind was against them now, and Piglet's ears\nstreamed behind him like banners as he fought his\nway along, and it seemed hours before he got them\ninto the shelter of the Hundred Acre Wood and they\nstood up straight again, to listen, a little\nnervously, to the roaring of the gale among the\ntreetops.\n\n\"Supposing a tree fell down, Pooh, when we were\nunderneath it?\"\n\n\"Supposing it didn't,\" said Pooh after careful\nthought.\n\nPiglet was comforted by this, and in a little\nwhile they were knocking and ringing very\ncheerfully at Owl's door.\n",
                 "There was a loud cracking noise.\n\n\"Look out!\" cried Pooh. \"Mind the clock! Out of\nthe way, Piglet! Piglet, I'm falling on you!\"\n\n\"Help!\" cried Piglet.\n\nPooh's side of the room was slowly tilting upwards\nand his chair began sliding down on Piglet's. The\nclock slithered gently along the mantelpiece,\ncollecting vases on the way, until they all\ncrashed together on to what had once been the\nfloor, but was now trying to see what it looked\nlike as a wall. Uncle Robert, who was going to be\nthe new hearthrug, and was bringing the rest of\nhis wall with him as carpet, met Piglet's chair\njust as Piglet was expecting to leave it.\n",
                 "\"Did I really do all that?\" he said at last.\n\n\"Well,\" said Pooh, \"in poetry - in a piece of\npoetry - well, you did it, Piglet, because the\npoetry says you did. And that's how people know.\"\n\n\"Oh!\" said Piglet. \"Because I - I thought I did\nblinch a little. Just at first. And it says, \"did\nhe blinch no no.\" That's why.\"\n\n\"You only blinched inside,\" said Pooh, \"and that's\nthe bravest way for a Very Small Animal not to\nblinch that there is.\"\n\nPiglet sighed with happiness, and began to think\nabout himself. He was BRAVE...\n",
                 "\"Aha!\" said Pooh. (Rum-tum-tiddle-um-tum.) \"If I\nknow anything about anything, that hole means\nRabbit,\" he said, \"and Rabbit means Company,\" he\nsaid, \"and Company means Food and\nListening-to-Me-Humming and such like.\nRum-tum-tum-tiddle-um.\"\n\nSo he bent down, put his head into the hole, and\ncalled out:\n\n\"Is anybody at home?\"\n\nThere was a sudden scuffling noise from inside the\nhole, and then silence.\n\n\"What I said was, \"Is anybody at home?\"\" called\nout Pooh very loudly.\n\n\"No!\" said a voice; and then added, \"You needn't\nshout so loud. I heard you quite well the first\ntime.\"\n",
                 "\"Bother!\" said Pooh. \"Isn't there anybody here at\nall?\"\n\n\"Nobody.\"\n\nWinnie-the-Pooh took his head out of the hole, and\nthought for a little, and he thought to himself,\n\"There must be somebody there, because somebody\nmust have said \"Nobody.\"\" So he put his head back\nin the hole, and said:\n\n\"Hallo, Rabbit, isn't that you?\"\n\n\"No,\" said Rabbit, in a different sort of voice\nthis time.\n\n\"But isn't that Rabbit's voice?\"\n\n\"I don't think so,\" said Rabbit. \"It isn't meant\nto be.\"\n",
                 "He took his head out of the hole, and had another\nthink, and then he put it back, and said:\n\n\"Well, could you very kindly tell me where Rabbit\nis?\"\n\n\"He has gone to see his friend Pooh Bear, who is a\ngreat friend of his.\"\n\n\"But this is Me!\" said Bear, very much surprised.\n\n\"What sort of Me?\"\n\n\"Pooh Bear.\"\n\n\"Are you sure?\" said Rabbit, still more surprised.\n\n\"Quite, quite sure,\" said Pooh.\n\n\"Oh, well, then, come in.\"\n\nSo Pooh pushed and pushed and pushed his way\nthrough the hole, and at last he got in.\n",
                 "\"Oh, help!\" said Pooh. \"I'd better go back.\"\n\n\"Oh, bother!\" said Pooh. \"I shall have to go on.\"\n\n\"I can't do either!\" said Pooh. \"Oh, help and\nbother!\"\n\nNow, by this time Rabbit wanted to go for a walk\ntoo, and finding the front door full, he went out\nby the back door, and came round to Pooh, and\nlooked at him.\n\n\"Hallo, are you stuck?\" he asked.\n\n\"N-no,\" said Pooh carelessly. \"Just resting and\nthinking and humming to myself.\"\n",
                 "Suddenly Winnie-the-Pooh stopped, and pointed\nexcitedly in front of him. \"Look!\"\n\n\"What?\" said Piglet, with a jump. And then, to\nshow that he hadn't been frightened, he jumped up\nand down once or twice more in an exercising sort\nof way.\n\n\"The tracks!\" said Pooh. \"A third animal has\njoined the other two!\"\n\n\"Pooh!\" cried Piglet. \"Do you think it is another\nWoozle?\"\n\n\"No,\" said Pooh, \"because it makes different\nmarks. It is either Two Woozles and one, as it\nmight be, Wizzle, or Two, as it might be, Wizzles\nand one, if so it is, Woozle. Let us continue to\nfollow them.\"\n",
                 "\"Do you see, Piglet? Look at their tracks! Three,\nas it were, Woozles, and one, as it was, Wizzle.\nAnother Woozle has joined them!\"\n\nAnd so it seemed to be. There were the tracks;\ncrossing over each other here, getting muddled up\nwith each other there; but, quite plainly every\nnow and then, the tracks of four sets of paws.\n\n\"I think,\" said Piglet, when he had licked the tip\nof his nose too, and found that it brought very\nlittle comfort, \"I think that I have just\nremembered something. I have just remembered\nsomething that I forgot to do yesterday and shan't\nbe able to do to-morrow. So I suppose I really\nought to go back and do it now.\"\n\n\"We'll do it this afternoon, and I'll come with\nyou,\" said Pooh.\n\n\"It isn't the sort of thing you can do in the\nafternoon,\" said Piglet quickly. \"It's a very\nparticular morning thing, that has to be done in\nthe morning.\"\n",
                 "\"The thing to do is as follows. First, Issue a\nReward. Then -\"\n\n\"Just a moment,\" said Pooh, holding up his paw.\n\"What do we do to this - what you were saying? You\nsneezed just as you were going to tell me.\"\n\n\"I didn't sneeze.\"\n\n\"Yes, you did, Owl.\"\n\n\"Excuse me, Pooh, I didn't. You can't sneeze\nwithout knowing it.\"\n\n\"Well, you can't know it without something having\nbeen sneezed.\"\n\n\"What I said was, \"First Issue a Reward\".\"\n\n\"You're doing it again,\" said Pooh sadly.\n",
                 "Where should they dig the Very Deep Pit?\n\nPiglet said that the best place would be somewhere\nwhere a Heffalump was, just before he fell into\nit, only about a foot farther on.\n\n\"But then he would see us digging it,\" said Pooh.\n\n\"Not if he was looking at the sky.\"\n\n\"He would Suspect,\" said Pooh, \"if he happened to\nlook down.\" He thought for a long time and then\nadded sadly, \"It isn't as easy as I thought. I\nsuppose that's why Heffalumps hardly ever get\ncaught.\"\n\n\"That must be it,\" said Piglet.\n",
                 "Piglet looked up from the bottom of his Very Deep\nPit, and said, \"Got it?\" and Pooh said, \"Yes, but\nit isn't quite a full jar,\" and he threw it down\nto Piglet, and Piglet said, \"No, it isn't! Is that\nall you've got left?\" and Pooh said \"Yes\". Because\nit was. So Piglet put the jar at the bottom of the\nPit, and climbed out, and they went off home\ntogether.\n\n\"Well, good night, Pooh,\" said Piglet, when they\nhad got to Pooh's house. \"And we meet at six\no'clock to-morrow morning by the Pine Trees, and\nsee how many Heffalumps we've got in our Trap.\"\n\n\"Six o'clock, Piglet. And have you got any\nstring?\"\n\n\"No. Why do you want string?\"\n\n\"To lead them home with.\"\n\n\"Oh!... I think Heffalumps come if you whistle.\"\n\n\"Some do and some don't. You never can tell with\nHeffalumps. Well, good night!\"\n",
                 "By and by Piglet woke up. As soon as he woke he\nsaid to himself, \"Oh!\" Then he said bravely,\n\"Yes,\" and then, still more bravely, \"Quite so.\"\nBut he didn't feel very brave, for the word which\nwas really jiggeting about in his brain was\n\"Heffalumps\".\n\nWhat was a Heffalump like?\n\nWas it Fierce?\n\nDid it come when you whistled? And how did it\ncome?\n\nWas it Fond of Pigs at all?\n\nIf it was Fond of Pigs, did it make any difference\nwhat sort of Pig?\n\nSupposing it was Fierce with Pigs, would it make\nany difference if the Pig had a grandfather called\nTRESPASSERS WILLIAM?\n",
                 "So at last he lifted up his head, jar and all, and\nmade a loud, roaring noise of Sadness and\nDespair... and it was at that moment that Piglet\nlooked down.\n\n\"Help, help!\" cried Piglet, \"a Heffalump, a\nHorrible Heffalump!\" and he scampered off as hard\nas he could, still crying out, \"Help, help, a\nHerrible Hoffalump! Hoff, Hoff, a Hellible\nHorralump! Holl, Holl, a Hoffable Hellerump!\" And\nhe didn't stop crying and scampering until he got\nto Christopher Robin's house.\n\n\"Whatever's the matter, Piglet?\" said Christopher\nRobin, who was just getting up.\n\n\"Heff,\" said Piglet, breathing so hard that he\ncould hardly speak, \"a Heff - a Heff - a\nHeffalump.\"\n",
                 "\"Good morning, Eeyore,\" said Pooh.\n\n\"Good morning, Pooh Bear,\" said Eeyore gloomily.\n\"If it is a good morning,\" he said. \"Which I\ndoubt,\" said he.\n\n\"Why, what's the matter?\"\n\n\"Nothing, Pooh Bear, nothing. We can't all, and\nsome of us don't. That's all there is to it.\"\n\n\"Can't all what?\" said Pooh, rubbing his nose.\n\n\"Gaiety. Song-and-dance. Here we go round the\nmulberry bush.\"\n\n\"Oh!\" said Pooh. He thought for a long time, and\nthen asked, \"What mulberry bush is that?\"\n\n\"Bon-hommy,\" went on Eeyore gloomily. \"French word\nmeaning bonhommy,\" he explained. \"I'm not\ncomplaining, but There It Is.\"\n",
                 "Pooh scratched his head, being a little puzzled by\nall this.\n\n\"But is it really your birthday?\" he asked.\n\n\"It is.\"\n\n\"Oh! Well, many happy returns of the day, Eeyore.\"\n\n\"And many happy returns to you, Pooh Bear.\"\n\n\"But it isn't my birthday.\"\n\n\"No, it's mine.\"\n\n\"But you said \"Many happy returns\" -\"\n\n\"Well, why not? You don't always want to be\nmiserable on my birthday, do you?\"\n\n\"Oh, I see,\" said Pooh.\n",
                 "\"Hallo, Piglet,\" he said.\n\n\"Hallo, Pooh,\" said Piglet.\n\n\"What are you trying to do?\"\n\n\"I was trying to reach the knocker,\" said Piglet.\n\"I just came round -\"\n\n\"Let me do it for you,\" said Pooh kindly. So he\nreached up and knocked at the door. \"I have just\nseen Eeyore,\" he began, \"and poor Eeyore is in a\nVery Sad Condition, because it's his birthday, and\nnobody has taken any notice of it, and he's very\nGloomy - you know what Eeyore is - and there he\nwas, and - What a long time whoever lives here is\nanswering this door.\" And he knocked again.\n\n\"But Pooh,\" said Piglet, \"it's your own house!\"\n\n\"Oh!\" said Pooh. \"So it is,\" he said. \"Well, let's\ngo in.\"\n\nSo in they went.\n",
                 "\"Lucky I brought this with me,\" he thought. \"Many\na bear going out on a warm day like this would\nnever have thought of bringing a little something\nwith him.\" And he began to eat.\n\n\"Now let me see,\" he thought as he took his last\nlick of the inside of the jar, \"where was I going?\nAh, yes, Eeyore.\" He got up slowly.\n\nAnd then, suddenly, he remembered. He had eaten\nEeyore's birthday present!\n\n\"Bother!\" said Pooh. \"What shall I do? I must give\nhim something.\"\n\nFor a little while he couldn't think of anything.\nThen he thought: \"Well, it's a very nice pot, even\nif there's no honey in it, and if I washed it\nclean, and got somebody to write \"A Happy\nBirthday\" on it, Eeyore could keep things in it,\nwhich might be Useful.\"\n",
                 "\"Is this it?\" said Owl, taking it out of Pooh's\npaw.\n\n\"Yes, and I wanted to ask you -\"\n\n\"Somebody has been keeping honey in it,\" said Owl.\n\n\"You can keep anything in it,\" said Pooh\nearnestly. \"It's Very Useful like that. And I\nwanted to ask you -\"\n\n\"You ought to write \"A Happy Birthday\" on it.\"\n\n\"That was what I wanted to ask you,\" said Pooh.\n\"Because my spelling is Wobbly. It's good spelling\nbut it Wobbles, and the letters get in the wrong\nplaces. Would you write \"A Happy Birthday\" on it\nfor me?\"\n",
                 "\"Good morning, Eeyore,\" shouted Piglet.\n\n\"Good morning, Little Piglet,\" said Eeyore. \"If it\nis a good morning,\" he said. \"Which I doubt,\" said\nhe. \"Not that it matters,\" he said.\n\n\"Many happy returns of the day,\" said Piglet,\nhaving now got closer.\n\nEeyore stopped looking at himself in the stream,\nand turned to stare at Piglet.\n\n\"Just say that again,\" he said.\n\n\"Many hap -\"\n\n\"Wait a moment.\"\n\nBalancing on three legs, he began to bring his\nfourth leg very cautiously up to his ear. \"I did\nthis yesterday,\" he explained, as he fell down for\nthe third time. \"It's quite easy. It's so as I can\nhear better... There, that's done it! Now then,\nwhat were you saying?\" He pushed his ear forward\nwith his hoof.\n\n\"Many happy returns of the day,\" said Piglet\nagain.\n",
                 "\"Me having a real birthday?\"\n\n\"Yes, Eeyore, and I've brought you a present.\"\n\nEeyore took down his right hoof from his right\near, turned round, and with great difficulty put\nup his left hoof.\n\n\"I must have that in the other ear,\" he said. \"Now\nthen.\"\n\n\"A present,\" said Piglet very loudly.\n\n\"Meaning me again?\"\n\n\"Yes.\"\n\n\"My birthday still?\"\n\n\"Of course, Eeyore.\"\n\n\"Me going on having a real birthday?\"\n\n\"Yes, Eeyore, and I brought you a balloon.\"\n",
                 "\"Balloon?\" said Eeyore. \"You did say balloon? One\nof those big coloured things you blow up? Gaiety,\nsong-and-dance, here we are and there we are?\"\n\n\"Yes, but I'm afraid - I'm very sorry, Eeyore -\nbut when I was running along to bring it you, I\nfell down.\"\n\n\"Dear, dear, how unlucky! You ran too fast, I\nexpect. You didn't hurt yourself, Little Piglet?\"\n\n\"No, but I - I - oh, Eeyore, I burst the balloon!\"\n\nThere was a very long silence.\n\n\"My balloon?\" said Eeyore at last.\n\nPiglet nodded.\n\n\"My birthday balloon?\"\n\n\"Yes, Eeyore,\" said Piglet sniffing a little.\n\"Here it is. With - with many happy returns of the\nday.\" And he gave Eeyore the small piece of damp\nrag.\n",
                 "\"Is this it?\" said Eeyore, a little surprised.\n\nPiglet nodded.\n\n\"My present?\"\n\nPiglet nodded again.\n\n\"The balloon?\"\n\n\"Yes.\"\n\n\"Thank you, Piglet,\" said Eeyore. \"You don't mind\nmy asking,\" he went on, \"but what colour was this\nballoon when it - when it was a balloon?\"\n\n\"Red.\"\n\n\"I just wondered... Red,\" he murmured to himself.\n\"My favourite colour... How big was it?\"\n\n\"About as big as me.\"\n\n\"I just wondered... About as big as Piglet,\" he\nsaid to himself sadly. \"My favourite size. Well,\nwell.\"\n",
                 "\"Many happy returns of the day,\" called out Pooh,\nforgetting that he had said it already.\n\n\"Thank you, Pooh, I'm having them,\" said Eeyore\ngloomily.\n\n\"I've brought you a little present,\" said Pooh\nexcitedly.\n\n\"I've had it,\" said Eeyore.\n\nPooh had now splashed across the stream to Eeyore,\nand Piglet was sitting a little way off, his head\nin his paws, snuffling to himself.\n\n\"It's a Useful Pot,\" said Pooh. \"Here it is. And\nit's got \"A Very Happy Birthday with love from\nPooh\" written on it. That's what all that writing\nis. And it's for putting things in. There!\"\n\nWhen Eeyore saw the pot, he became quite excited.\n",
                 "Well, Rabbit read this out proudly, and for a\nlittle while after he had read it nobody said\nanything. And then Piglet, who had been opening\nand shutting his mouth without making any noise,\nmanaged to say very huskily:\n\n\"And - Afterwards?\"\n\n\"How do you mean?\"\n\n\"When Kanga does Discover the Difference?\"\n\n\"Then we all say \"Aha!\"\"\n\n\"All three of us?\"\n\n\"Yes.\"\n\n\"Oh!\"\n\n\"Why, what's the trouble, Piglet?\"\n\n\"Nothing,\" said Piglet, \"as long as we all three\nsay it. As long as we all three say it,\" said\nPiglet, \"I don't mind,\" he said, \"but I shouldn't\ncare to say \"Aha!\" by myself. It wouldn't sound\nnearly so well.\"\n",
                 "\"Now then, Roo, dear,\" she said, as she took\nPiglet out of her pocket. \"Bed-time.\"\n\n\"Aha!\" said Piglet, as well as he could after his\nTerrifying Journey. But it wasn't a very good\n\"Aha!\" and Kanga didn't seem to understand what it\nmeant.\n\n\"Bath first,\" said Kanga in a cheerful voice.\n\n\"Aha!\" said Piglet again, looking round anxiously\nfor the others. But the others weren't there.\nRabbit was playing with Baby Roo in his own house,\nand feeling more fond of him every minute, and\nPooh, who had decided to be a Kanga, was still at\nthe sandy place on the top of the Forest,\npractising jumps.\n\n\"I am not at all sure,\" said Kanga in a thoughtful\nvoice, \"that it wouldn't be a good idea to have a\ncold bath this evening. Would you like that, Roo,\ndear?\"\n\nPiglet, who had never been really fond of baths,\nshuddered a long indignant shudder, and said in as\nbrave a voice as he could:\n\n\"Kanga, I see that the time has come to speak\nplainly.\"\n",
                 "\"I am looking, Roo, dear,\" said Kanga rather\nseverely. \"And you know what I told you yesterday\nabout making faces. If you go on making faces like\nPiglet's, you will grow up to look like Piglet -\nand then think how sorry you will be. Now then,\ninto the bath, and don't let me have to speak to\nyou about it again.\"\n\nBefore he knew where he was, Piglet was in the\nbath, and Kanga was scrubbing him firmly with a\nlarge lathery flannel.\n\n\"Ow!\" cried Piglet. \"Let me out! I'm Piglet!\"\n\n\"Don't open the mouth, dear, or the soap goes in,\"\nsaid Kanga. \"There! What did I tell you?\"\n\n\"You - you - you did it on purpose,\" spluttered\nPiglet, as soon as he could speak again... and\nthen accidentally had another mouthful of lathery\nflannel.\n",
                 "\"I'm not asking anybody,\" said Eeyore. \"I'm just\ntelling everybody. We can look for the North Pole,\nor we can play \"Here we go gathering Nuts and May\"\nwith the end part of an ant's nest. It's all the\nsame to me.\"\n\nThere was a shout from the top of the line.\n\n\"Come on!\" called Christopher Robin.\n\n\"Come on!\" called Pooh and Piglet.\n\n\"Come on!\" called Owl.\n\n\"We're starting,\" said Rabbit. \"I must go.\" And he\nhurried off to the front of the Expotition with\nChristopher Robin.\n\n\"All right,\" said Eeyore. \"We're going. Only Don't\nBlame Me.\"\n\nSo off they all went to discover the Pole.\n",
                 "\"An Ambush,\" said Owl, \"is a sort of Surprise.\"\n\n\"So is a gorse-bush sometimes,\" said Pooh.\n\n\"An Ambush, as I was about to explain to Pooh,\"\nsaid Piglet, \"is a sort of Surprise.\"\n\n\"If people jump out at you suddenly, that's an\nAmbush,\" said Owl.\n\n\"It's an Ambush, Pooh, when people jump at you\nsuddenly,\" explained Piglet.\n\nPooh, who now knew what an Ambush was, said that a\ngorse-bush had sprung at him suddenly one day when\nhe fell off a tree, and he had taken six days to\nget all the prickles out of himself.\n\n\"We are not talking about gorse-bushes,\" said Owl\na little crossly.\n\n\"I am,\" said Pooh.\n",
                 "\"I think,\" said Christopher Robin, \"that we ought\nto eat all our Provisions now, so that we shan't\nhave so much to carry.\"\n\n\"Eat all our what?\" said Pooh.\n\n\"All that we've brought,\" said Piglet, getting to\nwork.\n\n\"That's a good idea,\" said Pooh, and he got to\nwork too.\n\n\"Have you all got something?\" asked Christopher\nRobin with his mouth full.\n\n\"All except me,\" said Eeyore. \"As Usual.\" He\nlooked round at them in his melancholy way. \"I\nsuppose none of you are sitting on a thistle by\nany chance?\"\n\n\"I believe I am,\" said Pooh. \"Ow!\" He got up, and\nlooked behind him. \"Yes, I was. I thought so.\"\n\n\"Thank you, Pooh. If you've quite finished with\nit.\" He moved across to Pooh's place, and began to\neat.\n",
                 "They went back to the others. Piglet was lying on\nhis back, sleeping peacefully. Roo was washing his\nface and paws in the stream, while Kanga explained\nto everybody proudly that this was the first time\nhe had ever washed his face himself, and Owl was\ntelling Kanga an Interesting Anecdote full of long\nwords like Encyclopedia and Rhododendron to which\nKanga wasn't listening.\n\n\"I don't hold with all this washing,\" grumbled\nEeyore. \"This modern Behind-the-ears nonsense.\nWhat do you think, Pooh?\"\n\n\"Well, said Pooh, \"I think -\"\n\nBut we shall never know what Pooh thought, for\nthere came a sudden squeak from Roo, a splash, and\na loud cry of alarm from Kanga.\n\n\"So much for washing,\" said Eeyore.\n\n\"Roo's fallen in!\" cried Rabbit, and he and\nChristopher Robin came rushing down to the rescue.\n",
                 "Eeyore was sitting with his tail in the water when\nthey all got back to him.\n\n\"Tell Roo to be quick, somebody,\" he said. \"My\ntail's getting cold. I don't want to mention it,\nbut I just mention it. I don't want to complain,\nbut there it is. My tail's cold.\"\n\n\"Here I am!\" squeaked Roo.\n\n\"Oh, there you are.\"\n\n\"Did you see me swimming?\"\n\nEeyore took his tail out of the water, and swished\nit from side to side.\n\n\"As I expected,\" he said. \"Lost all feeling.\nNumbed it. That's what it's done. Numbed it. Well,\nas long as nobody minds, I suppose it's all\nright.\"\n\n\"Poor old Eeyore. I'll dry it for you,\" said\nChristopher Robin, and he took out his\nhandkerchief and rubbed it up.\n\n\"Thank you, Christopher Robin. You're the only one\nwho seems to understand about tails. They don't\nthink - that's what's the matter with some of\nthese others. They've no imagination. A tail isn't\na tail to them, it's just a Little Bit Extra at\nthe back.\"\n",
                 "\"It's a little Anxious,\" he said to himself, \"to\nbe a Very Small Animal Entirely Surrounded by\nWater. Christopher Robin and Pooh could escape by\nClimbing Trees, and Kanga could escape by Jumping,\nand Rabbit could escape by Burrowing, and Owl\ncould escape by Flying, and Eeyore could escape by\n- by Making a Loud Noise Until Rescued, and here\nam I, surrounded by water and I can't do\nanything.\"\n\nThen suddenly he remembered a story which\nChristopher Robin had told him about a man on a\ndesert island who had written something in a\nbottle and thrown it in the sea; and Piglet\nthought that if he wrote something in a bottle and\nthrew it in the water, perhaps somebody would come\nand rescue him!\n\nHe left the window and began to search his house,\nall of it that wasn't under water, and at last he\nfound a pencil and a small piece of dry paper, and\na bottle with a cork to it. And he wrote on one\nside of the paper:\n\nHELP! PIGLIT (ME)\n\nand on the other side:\n\nIT'S ME PIGLIT, HELP HELP.\n",
                 "When the rain began Pooh was asleep. It rained,\nand it rained, and it rained, and he slept and he\nslept and he slept. He had had a tiring day. You\nremember how he discovered the North Pole; well,\nhe was so proud of this that he asked Christopher\nRobin if there were any other Poles such as a Bear\nof Little Brain might discover.\n\n\"There's a South Pole,\" said Christopher Robin,\n\"and I expect there's an East Pole and a West\nPole, though people don't like talking about\nthem.\"\n\nPooh was very excited when he heard this, and\nsuggested that they should have an Expotition to\ndiscover the East Pole, but Christopher Robin had\nthought of something else to do with Kanga; so\nPooh went out to discover the East Pole by\nhimself. Whether he discovered it or not, I\nforget; but he was so tired when he got home that,\nin the very middle of his supper, after he had\nbeen eating for little more than half-an-hour, he\nfell fast asleep in his chair, and slept and slept\nand slept.\n",
                 "He splashed to his door and looked out...\n\n\"This is Serious,\" said Pooh. \"I must have an\nEscape.\"\n\nSo he took his largest pot of honey and escaped\nwith it to a broad branch of his tree, well above\nthe water, and then he climbed down again and\nescaped with another pot... and when the whole\nEscape was finished, there was Pooh sitting on his\nbranch dangling his legs, and there, beside him,\nwere ten pots of honey...\n\nTwo days later, there was Pooh, sitting on his\nbranch, dangling his legs, and there, beside him,\nwere four pots of honey...\n\nThree days later, there was Pooh, sitting on his\nbranch, dangling his legs, and there beside him,\nwas one pot of honey.\n\nFour days later, there was Pooh...\n",
                 "And it was on the morning of the fourth day that\nPiglet's bottle came floating past him, and with\none loud cry of \"Honey!\" Pooh plunged into the\nwater, seized the bottle, and struggled back to\nhis tree again.\n\n\"Bother!\" said Pooh, as he opened it. \"All that\nwet for nothing. What's that bit of paper doing?\"\n\nHe took it out and looked at it.\n\n\"It's a Missage,\" he said to himself, \"that's what\nit is. And that letter is a \"P\", and so is that,\nand so is that, and \"P\" means \"Pooh\", so it's a\nvery important Missage to me, and I can't read it.\nI must find Christopher Robin or Owl or Piglet,\none of those Clever Readers who can read things,\nand they will tell me what this missage means.\nOnly I can't swim. Bother!\"\n",
                 "Then he had an idea, and I think that for a Bear\nof Very Little Brain, it was a good idea. He said\nto himself:\n\n\"If a bottle can float, then a jar can float, and\nif a jar floats, I can sit on the top of it, if\nit's a very big jar.\"\n\nSo he took his biggest jar, and corked it up. \"All\nboats have to have a name,\" he said, \"so I shall\ncall mine The Floating Bear.\" And with these words\nhe dropped his boat into the water and jumped in\nafter it.\n\nFor a little while Pooh and The Floating Bear were\nuncertain as to which of them was meant to be on\nthe top, but after trying one or two different\npositions, they settled down with The Floating\nBear underneath and Pooh triumphantly astride it,\npaddling vigorously with his feet.\n",
                 "It was on this morning that Owl came flying over\nthe water to say \"How do you do?\" to his friend\nChristopher Robin.\n\n\"I say, Owl,\" said Christopher Robin, \"isn't this\nfun? I'm on an island!\"\n\n\"The atmospheric conditions have been very\nunfavourable lately,\" said Owl.\n\n\"The what?\"\n\n\"It has been raining,\" explained Owl.\n\n\"Yes,\" said Christopher Robin. \"It has.\"\n\n\"The flood-level has reached an unprecedented\nheight.\"\n\n\"The who?\"\n\n\"There's a lot of water about,\" explained Owl.\n\n\"Yes,\" said Christopher Robin, \"there is.\"\n",
                 "\"Now then, Pooh,\" said Christopher Robin, \"where's\nyour boat?\"\n\n\"I ought to say,\" explained Pooh as they walked\ndown to the shore of the island, \"that it isn't\njust an ordinary sort of boat. Sometimes it's a\nBoat, and sometimes it's more of an Accident. It\nall depends.\"\n\n\"Depends on what?\"\n\n\"On whether I'm on top of it or underneath it.\"\n\n\"Oh! Well, where is it?\"\n\n\"There!\" said Pooh, pointing proudly to The\nFloating Bear.\n\nIt wasn't what Christopher Robin expected, and the\nmore he looked at it, the more he thought what a\nBrave and Clever Bear Pooh was, and the more\nChristopher Robin thought this, the more Pooh\nlooked modestly down his nose and tried to pretend\nhe wasn't.\n",
                 "And then this Bear, Pooh Bear, Winnie-the-Pooh,\nF.O.P. (Friend of Piglet's), R.C. (Rabbit's\nCompanion), P.D. (Pole Discoverer), E.C. and T.F.\n(Eeyore's Comforter and Tail-finder) - in fact,\nPooh himself - said something so clever that\nChristopher Robin could only look at him with\nmouth open and eyes staring, wondering if this was\nreally the Bear of Very Little Brain whom he had\nknow and loved so long.\n\n\"We might go in your umbrella,\" said Pooh.\n\n\"?\"\n\n\"We might go in your umbrella,\" said Pooh.\n\n\"??\"\n\n\"We might go in your umbrella,\" said Pooh.\n\n\"!!!!!!\"\n\nFor suddenly Christopher Robin saw that they\nmight.\n",
                 "\"Hallo, Eeyore,\" said Christopher Robin, as he\nopened the door and came out. \"How are you?\"\n\n\"It's snowing still,\" said Eeyore gloomily.\n\n\"So it is.\"\n\n\"And freezing.\"\n\n\"Is it?\"\n\n\"Yes,\" said Eeyore. \"However,\" he said,\nbrightening up a little, \"we haven't had an\nearthquake lately.\"\n\n\"What's the matter, Eeyore?\"\n\n\"Nothing, Christopher Robin. Nothing important. I\nsuppose you haven't seen a house or what-not\nanywhere about?\"\n",
                 "\"I don't know how it is, Christopher Robin, but\nwhat with all this snow and one thing and another,\nnot to mention icicles and such-like, it isn't so\nHot in my field about three o'clock in the morning\nas some people think it is. It isn't Close, if you\nknow what I mean - not so as to be uncomfortable.\nIt isn't Stuffy. In fact, Christopher Robin,\" he\nwent on in a loud whisper,\n\"quite-between-ourselves and don't-tell-anybody,\nit's Cold.\"\n\n\"Oh, Eeyore!\"\n\n\"And I said to myself: The others will be sorry if\nI'm getting myself all cold. They haven't got\nBrains, any of them, only grey fluff that's blown\ninto their heads by mistake, and they don't Think,\nbut if it goes on snowing for another six weeks or\nso, one of them will begin to say to himself:\n\"Eeyore can't be so very much too Hot about three\no'clock in the morning.\" And then it will Get\nAbout. And they'll be Sorry.\"\n\n\"Oh, Eeyore!\" said Christopher Robin, feeling very\nsorry already.\n",
                 "\"Hallo, Pooh,\" said Piglet.\n\n\"Hallo, Piglet. This is Tigger.\"\n\n\"Oh, is it?\" said Piglet, and he edged round to\nthe other side of the table. \"I thought Tiggers\nwere smaller than that.\"\n\n\"Not the big ones,\" said Tigger.\n\n\"They like haycorns,\" said Pooh, \"so that's what\nwe've come for, because poor Tigger hasn't had any\nbreakfast yet.\"\n\nPiglet pushed the bowl of haycorns towards Tigger,\nand said, \"Help yourself,\" and then he got close\nup to Pooh and felt much braver, and said, \"So\nyou're Tigger? Well, well!\" in a careless sort of\nvoice. But Tigger said nothing because his mouth\nwas full of haycorns...\n\nAfter a long munching noise he said:\n\n\"Ee-ers o i a-ors.\"\n",
                 "\"I knew there was something,\" said Pooh. \"Tiggers\nalways eat thistles, so that was why we came to\nsee you, Eeyore.\"\n\n\"Don't mention it, Pooh.\"\n\n\"Oh, Eeyore, I didn't mean that I didn't want to\nsee you -\"\n\n\"Quite - quite. But your new stripy friend -\nnaturally, he wants his breakfast. What did you\nsay his name was?\"\n\n\"Tigger.\"\n\n\"Then come this way, Tigger.\"\n\nEeyore led the way to the most thistly-looking\npatch of thistles that ever was, and waved a hoof\nat it.\n\n\"A little patch I was keeping for my birthday,\" he\nsaid; \"but, after all, what are birthdays? Here\nto-day and gone to-morrow. Help yourself, Tigger.\"\n",
                 "Piglet was busy digging a small hole in the ground\noutside his house.\n\n\"Hallo, Piglet,\" said Pooh.\n\n\"Hallo, Pooh,\" said Piglet, giving a jump of\nsurprise. \"I knew it was you.\"\n\n\"So did I,\" said Pooh. \"What are you doing?\"\n\n\"I'm planting a haycorn, Pooh, so that it can grow\nup into an oak-tree, and have lots of haycorns\njust outside the front door instead of having to\nwalk miles and miles, do you see, Pooh?\"\n\n\"Supposing it doesn't?\" said Pooh.\n\n\"It will, because Christopher Robin says it will,\nso that's why I'm planting it.\"\n\n\"Well,\" said Pooh, \"if I plant a honeycomb outside\nmy house, then it will grow up into a beehive.\"\n",
                 "\"Look, Pooh!\" said Piglet suddenly. \"There's\nsomething in one of the Pine Trees.\"\n\n\"So there is!\" said Pooh, looking up wonderingly.\n\"There's an Animal.\"\n\nPiglet took Pooh's arm, in case Pooh was\nfrightened.\n\n\"Is it One of the Fiercer Animals?\" he said,\nlooking the other way.\n\nPooh nodded.\n\n\"It's a Jagular,\" he said.\n\n\"What do Jagulars do?\" asked Piglet, hoping that\nthey wouldn't.\n\n\"They hide in the branches of trees, and drop on\nyou as you go underneath,\" said Pooh. \"Christopher\nRobin told me.\"\n",
                 "\"Perhaps we better hadn't go underneath, Pooh. In\ncase he dropped and hurt himself.\"\n\n\"They don't hurt themselves,\" said Pooh. \"They're\nsuch very good droppers.\"\n\nPiglet still felt that to be underneath a Very\nGood Dropper would be a Mistake, and he was just\ngoing to hurry back for something which he had\nforgotten when the Jagular called out to them.\n\n\"Help! Help!\" it called.\n\n\"That's what Jagulars always do,\" said Pooh, much\ninterested. \"They call \"Help! Help!\" and then when\nyou look up, they drop on you.\"\n\n\"I'm looking down,\" cried Piglet loudly, so as the\nJagular shouldn't do the wrong thing by accident.\n",
                 "\"Look out!\" cried Christopher Robin to the others.\n\nThere was a crash, and a tearing noise, and a\nconfused heap of everybody on the ground.\n\nChristopher Robin and Pooh and Piglet picked\nthemselves up first, and then they picked Tigger\nup, and underneath everybody else was Eeyore.\n\n\"Oh, Eeyore!\" cried Christopher Robin. \"Are you\nhurt?\" And he felt him rather anxiously, and\ndusted him and helped him to stand up again.\n\nEeyore said nothing for a long time. And then he\nsaid: \"Is Tigger there?\"\n\nTigger was there, feeling Bouncy again already.\n\n\"Yes,\" said Christopher Robin. \"Tigger's here.\"\n\n\"Well, just thank him for me,\" said Eeyore.\n",
                 "Looking very calm, very dignified, with his legs\nin the air, came Eeyore from beneath the bridge.\n\n\"It's Eeyore!\" cried Roo, terribly excited.\n\n\"Is that so?\" said Eeyore, getting caught up by a\nlittle eddy, and turning slowly round three times.\n\"I wondered.\"\n\n\"I didn't know you were playing,\" said Roo.\n\n\"I'm not,\" said Eeyore.\n\n\"Eeyore, what are you doing there?\" said Rabbit.\n\n\"I'll give you three guesses, Rabbit. Digging\nholes in the ground? Wrong. Leaping from branch to\nbranch of a young oak-tree? Wrong. Waiting for\nsomebody to help me out of the river? Right. Give\nRabbit time, and he'll always get the answer.\"\n",
                 "\"Eeyore, what are you doing there?\" said Rabbit.\n\n\"I'll give you three guesses, Rabbit. Digging\nholes in the ground? Wrong. Leaping from branch to\nbranch of a young oak-tree? Wrong. Waiting for\nsomebody to help me out of the river? Right. Give\nRabbit time, and he'll always get the answer.\"\n\n\"But, Eeyore,\" said Pooh in distress, \"what can we\n- I mean, how shall we - do you think if we -\"\n\n\"Yes,\" said Eeyore. \"One of those would be just\nthe thing. Thank you, Pooh.\"\n\n\"He's going round and round,\" said Roo, much\nimpressed.\n\n\"And why not?\" said Eeyore coldly.\n\n\"I can swim too,\" said Roo proudly.\n\n\"Not round and round,\" said Eeyore. \"It's much\nmore difficult.\"\n",
                 "\"I've got a sort of idea,\" said Pooh at last, \"but\nI don't suppose it's a very good one.\"\n\n\"I don't suppose it is either,\" said Eeyore.\n\n\"Go on, Pooh,\" said Rabbit. \"Let's have it.\"\n\n\"Well, if we all threw stones and things into the\nriver on one side of Eeyore, the stones would make\nwaves, and the waves would wash him to the other\nside.\"\n\n\"That's a very good idea,\" said Rabbit, and Pooh\nlooked happy again.\n\n\"Very,\" said Eeyore. \"When I want to be washed,\nPooh, I'll let you know.\"\n\n\"Supposing we hit him by mistake?\" said Piglet\nanxiously.\n\n\"Or supposing you missed him by mistake,\" said\nEeyore. \"Think of all the possibilities, Piglet,\nbefore you settle down to enjoy yourselves.\"\n",
                 "Pooh had got the biggest stone he could carry, and\nwas leaning over the bridge, holding it in his\npaws.\n\n\"I'm not throwing it, I'm dropping it, Eeyore,\"\nhe explained. \"And then I can't miss - I mean I\ncan't hit you. Could you stop turning round for a\nmoment, because it muddles me rather?\"\n\n\"No,\" said Eeyore. \"I like turning round.\"\n\nRabbit began to feel that it was time he took\ncommand.\n\n\"Now, Pooh,\" he said, \"when I say \"Now!\" you can\ndrop it. Eeyore, when I say \"Now!\" Pooh will drop\nhis stone.\"\n\n\"Thank you very much, Rabbit, but I expect I shall\nknow.\"\n\n\"Are you ready, Pooh? Piglet, give Pooh a little\nmore room. Get back a bit there, Roo. Are you\nready?\"\n\n\"No,\" said Eeyore.\n\n\"Now!\" said Rabbit.\n\nPooh dropped his stone. There was a loud splash,\nand Eeyore disappeared...\n",
                 "\"How did you fall in, Eeyore?\" asked Rabbit, as he\ndried him with Piglet's handkerchief.\n\n\"I didn't,\" said Eeyore.\n\n\"But how -\"\n\n\"I was BOUNCED,\" said Eeyore.\n\n\"Oo,\" said Roo excitedly, \"did somebody push you?\"\n\n\"Somebody BOUNCED me. I was just thinking by the\nside of the river - thinking, if any of you know\nwhat that means - when I received a loud BOUNCE.\"\n\n\"Oh, Eeyore!\" said everybody.\n\n\"Are you sure you didn't slip?\" asked Rabbit\nwisely.\n\n\"Of course I slipped. If you're standing on the\nslippery bank of a river, and somebody BOUNCES you\nloudly from behind, you slip. What did you think I\ndid?\"\n",
                 "\"Hallo, everybody,\" said Tigger cheerfully.\n\n\"Hallo, Tigger,\" said Roo.\n\nRabbit became very important suddenly.\n\n\"Tigger,\" he said solemnly, \"what happened just\nnow?\"\n\n\"Just when?\" said Tigger a little uncomfortably.\n\n\"When you bounced Eeyore into the river.\"\n\n\"I didn't bounce him.\"\n\n\"You bounced me,\" said Eeyore gruffly.\n\n\"I didn't really. I had a cough, and I happened to\nbe behind Eeyore, and I said\n\"Grrr-oppp-ptschschschz.\"\"\n\n\"Why?\" said Rabbit, helping Piglet up, and dusting\nhim. \"It's all right, Piglet.\"\n\n\"It took me by surprise,\" said Piglet nervously.\n\n\"That's what I call bouncing,\" said Eeyore.\n\"Taking people by surprise. Very unpleasant\nhabit.\"\n",
                 "\"Owl,\" said Pooh, \"I have thought of something.\"\n\n\"Astute and Helpful Bear,\" said Owl.\n\nPooh looked proud at being called a stout and\nhelpful bear, and said modestly that he just\nhappened to think of it. You tied a piece of\nstring to Piglet, and you flew up to the\nletter-box, with the other end in your beak, and\nyou pushed it through the wire and brought it down\nto the floor, and you and Pooh pulled hard at this\nend, and Piglet went slowly up at the other end.\nAnd there you were.\n\n\"And there Piglet is,\" said Owl. \"If the string\ndoesn't break.\"\n\n\"Supposing it does?\" asked Piglet, really wanting\nto know.\n\n\"Then we try another piece of string.\"\n",
                 "\"Now then, Eeyore,\" he said.\n\n\"Don't Bustle me,\" said Eeyore, getting up slowly.\n\"Don't now-then me.\" He took a piece of paper from\nbehind his ear, and unfolded it. \"Nobody knows\nanything about this,\" he went on. \"This is a\nSurprise.\" He coughed in an important way, and\nbegan again: \"What-nots and Etceteras, before I\nbegin, or perhaps I should say, before I end, I\nhave a piece of Poetry to read to you. Hitherto -\nhitherto - a long word meaning - well, you'll see\nwhat it means directly - hitherto, as I was\nsaying, all the Poetry in the Forest has been\nwritten by Pooh, a Bear with a Pleasing Manner but\na Positively Startling Lack of Brain. The Poem\nwhich I am now about to read to you was written by\nEeyore, or Myself, in a Quiet Moment. If somebody\nwill take Roo's bull's eye away from him, and wake\nup Owl, we shall all be able to enjoy it. I call\nit - POEM.\"\n",
                 "\"Is it a very Grand thing to be an Afternoon, what\nyou said?\"\n\n\"A what?\" said Christopher Robin lazily, as he\nlistened to something else.\n\n\"On a horse,\" explained Pooh.\n\n\"A Knight?\"\n\n\"Oh, was that it?\" said Pooh. \"I thought it was a\n- Is it as Grand as a King and Factors and all the\nother things you said?\"\n\n\"Well, it's not as grand as a King,\" said\nChristopher Robin, and then, as Pooh seemed\ndisappointed, he added quickly, \"but it's grander\nthan Factors.\"\n\n\"Could a Bear be one?\"\n\n\"Of course he could!\" said Christopher Robin.\n\"I'll make you one.\" And he took a stick and\ntouched Pooh on the shoulder, and said, \"Rise, Sir\nPooh de Bear, most faithful of all my Knights.\"\n\nSo Pooh rose and sat down and said \"Thank you,\"\nwhich is a proper thing to say when you have been\nmade a Knight.\n",
                 "\"Pooh, when I'm - you know - when I'm not doing\nNothing, will you come up here sometimes?\"\n\n\"Just Me?\"\n\n\"Yes, Pooh.\"\n\n\"Will you be here too?\"\n\n\"Yes, Pooh, I will be really. I promise I will be,\nPooh.\"\n\n\"That's good,\" said Pooh.\n\n\"Pooh, promise you won't forget about me, ever.\nNot even when I'm a hundred.\"\n\nPooh thought for a little.\n\n\"How old shall I be then?\"\n\n\"Ninety-nine.\"\n\nPooh nodded.\n\n\"I promise,\" he said.\n"};
}
void TaskC::generate_task_test(int task_num)
{
    init_random_test_files_name(test_files, 2);

    int num1 = rand() % text_data.size();

    f1 = open(test_files[0].c_str(), O_RDWR | O_CREAT, 0644);
    write(f1, text_data[num1].c_str(), text_data[num1].size());
    lseek(f1, 0, SEEK_SET);

    if (task_num == 2 || task_num == 4 || task_num == 13)
    {
        use_flag = true;
        int num2 = rand() % text_data.size();

        while (num2 == num1)
        {
            num2 = rand() % sizeof(text_data);
        }

        f2 = open(test_files[1].c_str(), O_RDWR | O_CREAT, 0644);
        write(f2, text_data[num2].c_str(), text_data[num2].size());
        lseek(f2, 0, SEEK_SET);
    }

    int slen = rand() % 10 + 20;
    for (int i = 0; i < slen; i++)
        S[i] = (char)(rand() % 26 + 65);
    S[slen] = '\n';
    S[slen + 1] = '\0';
    K = rand() % 10 + 5;
}
void TaskC::test1()
{
    execute_argv.push_back(S);
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
    write(f_control, S, strlen(S));
}
void TaskC::test2()
{
    execute_argv.push_back(test_files[0]);
    execute_argv.push_back(test_files[1]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
    while ((n = read_line(f2, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
}
void TaskC::test3()
{
    execute_argv.push_back(S);
    execute_argv.push_back(test_files[0]);

    write(f_control, S, strlen(S));
    while ((n = read_line(f1, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
}
void TaskC::test4()
{
    execute_argv.push_back(test_files[0]);
    execute_argv.push_back(test_files[1]);

    while ((n = read_line(f2, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
    while ((n = read_line(f1, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
}
void TaskC::test5()
{
    execute_argv.push_back(std::to_string(K));
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        j++;
        if (j == K)
        {
            write(f_control, &empty, 1);
        }
        write(f_control, buf, n);
    }
}
void TaskC::test6()
{
    execute_argv.push_back(std::to_string(K));
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        j++;
        write(f_control, buf, n);
        if (j == K)
        {
            write(f_control, &empty, 1);
        }
    }
}
void TaskC::test7()
{
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        write(f_control, buf, n);
        if (n == 1)
        {
            write(f_control, &empty, 1);
        }
    }
}
void TaskC::test8()
{
    execute_argv.push_back(S);
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        if (n == 1)
        {
            write(f_control, S, strlen(S));
        }
        else
        {
            write(f_control, buf, n);
        }
    }
}
void TaskC::test9()
{
    execute_argv.push_back(test_files[0]);

    read_line(f1, buf, 200);
    while ((n = read_line(f1, buf, 200)) > 0)
    {
        write(f_control, buf, n);
    }
}
void TaskC::test10()
{
    execute_argv.push_back(test_files[0]);
    n = read_line(f1, buf, 200);
    while ((n2 = read_line(f1, buf2, 200)) > 0)
    {
        write(f_control, buf, n);
        n = n2;
        strcpy(buf, buf2);
    }
}
void TaskC::test11()
{
    execute_argv.push_back(std::to_string(K));
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        j++;
        if (j != K)
        {
            write(f_control, buf, n);
        }
    }
}
void TaskC::test12()
{
    execute_argv.push_back(test_files[0]);
    while ((n = read_line(f1, buf, 200)) > 0)
    {
        if (n > 1)
        {
            write(f_control, buf, n);
        }
    }
}
void TaskC::test13()
{
    execute_argv.push_back(test_files[0]);
    execute_argv.push_back(test_files[1]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        n2 = read_line(f2, buf2, 200);
        if (n2 > 0)
        {
            buf[n - 1] = '\0';
            strcat(buf, buf2);
        }
        write(f_control, buf, strlen(buf));
    }
}
void TaskC::test14()
{
    execute_argv.push_back(std::to_string(K));
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        if (n - 1 > K)
        {
            memmove(buf, buf + K, n - K + 1);
        }
        else
        {
            buf[0] = '\n';
            buf[1] = '\0';
        }
        write(f_control, buf, strlen(buf));
    }
}
void TaskC::test15()
{
    execute_argv.push_back(std::to_string(K));
    execute_argv.push_back(test_files[0]);

    while ((n = read_line(f1, buf, 200)) > 0)
    {
        if (n - 1 > K)
        {
            memmove(buf + n - K - 1, buf + n - 1, 2);
        }
        else
        {
            buf[0] = '\n';
            buf[1] = '\0';
        }
        write(f_control, buf, strlen(buf));
    }
}
void TaskC::test16()
{
    execute_argv.push_back(test_files[0]);
    while ((n = read_line(f1, buf, 200)) > 0)
    {
        for (j = 0; j < n; j++)
        {
            if (isupper(buf[j]))
            {
                buf[j] = tolower(buf[j]);
            }
            else if (islower(buf[j]))
            {
                buf[j] = toupper(buf[j]);
            }
        }
        write(f_control, buf, n);
    }
}
void TaskC::generate_task_control(int task_num)
{
    execute_argv.clear();
    f_control = open(control_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    switch (task_num)
    {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    case 4:
        test4();
        break;
    case 5:
        test5();
        break;
    case 6:
        test6();
        break;
    case 7:
        test7();
        break;
    case 8:
        test8();
        break;
    case 9:
        test9();
        break;
    case 10:
        test10();
        break;
    case 11:
        test11();
        break;
    case 12:
        test12();
        break;
    case 13:
        test13();
        break;
    case 14:
        test14();
        break;
    case 15:
        test15();
        break;
    case 16:
        test16();
        break;
    }

    close(f_control);
    close(f1);
    if (use_flag)
    {
        close(f2);
    }
}
void TaskC::print_extral_info(int task_num)
{
    if (use_flag)
    {
        show_file(test_files[0], "Input file1: ", 2);
        show_file(test_files[1], "Input file2: ", 2);
    }
    else
    {
        show_file(test_files[0], "Input file: ", 2);
    }
}
int TaskC::check_program(int task_num) const
{
    show_file(test_files[0], "Result file: ", 2);

    return compare_file(test_files[0], control_file);
}