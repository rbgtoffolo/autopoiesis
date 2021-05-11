s.boot
(
//Global Vars
~numOfSynths = 5;
~numOfPartials = 12;
// ~arrayFreqs = List.new;
// ~arrayAmps = List.new;
// ~arrayOfSynths = List.new;

// Synth
SynthDef.new(\sine, {
	arg freq=440, amp = 0.5, gate = 0;
	var sig, env;
	env = EnvGen.kr(Env.adsr, gate);
	sig = SinOsc.ar(freq);
	sig = sig*amp*env;
	Out.ar(0, sig!2);
}).add;

// recebe ofOsc /of/setup/numOfBalls, numOfPartials
// cria List para Frequencias, Amplitudes e para Synths



OSCdef.new(\setup,
	{
		arg msg;
		msg.postln;
		~numOfSynths = msg[1];
		~numOfPartials = msg[2];
		~arrayOfFreqs = List.new;
		~arrayOfAmps = List.new;
		~arrayOfSynths = List.new;
		~numOfSynths.do({
			arg i;
			~arrayOfFreqs.add(List.new);
			~arrayOfAmps.add(List.new);
			~arrayOfSynths.add(List.new);
			~numOfPartials.do({
				arg j;
				~arrayOfFreqs[i].add(0);
				~arrayOfAmps[i].add(0);
				~arrayOfSynths[i].add(0);
			});
		});

},'/of/setup');


// recebe ofOsc /of/setSynths/id,freq0,amp0.freq1,amp1,...
// atualiza List de Frequencias, Amplitudes e Instacia um synth para cada harmonico
OSCdef.new(\setSynths, {
	arg msg;

	var id = msg[1].asInt; // id de Ball - valor do array externo
	msg.postln;
	~numOfPartials.do({
		arg i;
		var freq, amp;
		freq = msg[(i*2)+2];
		amp = msg[(i*2)+3];
		~arrayOfFreqs[id][i] = freq;
		~arrayOfAmps[id][i] = amp;
		~arrayOfSynths[id][i] = Synth(\sine, [\freq, freq, \amp, amp, \gate, 1]);
	});
},'/of/setSynths');


//recebe ofOsc /of/updateAmps/id, amp0, amp1, amp2, amp...
//atualiza os synths
OSCdef.new(\updateAmps, {
	arg msg;

	var id = msg[1].asInt;
	msg.postln;
	~numOfPartials.do({
			arg i;
			var amp;
		amp = msg[i+2];
		~arrayOfAmps[id][i] = amp;
		~arrayOfSynths[id][i].set(\amp, amp);
	})
},'/of/updateAmps');


)

