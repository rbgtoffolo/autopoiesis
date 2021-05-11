s.boot
(
//Global Vars
//~numOfSynths = 5;
//numOfPartials = 12;
// ~arrayFreqs = List.new;
// ~arrayAmps = List.new;
// ~arrayOfSynths = List.new;

// Synth

SynthDef.new(\sine, {
	arg freq=440, amp = 1, gate = 0, pan = 0;
	var sig, env, vib, noise;
	env = EnvGen.kr(Env.adsr, gate);
	vib = LFNoise2.kr(5)*3;
	sig = SinOsc.ar(freq+vib,amp);
	sig = sig*amp*env;
	sig = Pan2.ar(sig, pan);
//	sig = FreeVerb.ar(sig, 0.8, amp, amp);
	Out.ar(0, sig);
}).add;


// SynthDef.new(\sineOld, {
// 	arg freq=440, amp = 1, gate = 0, pan = 0;
// 	var sig, env;
// 	env = EnvGen.kr(Env.adsr, gate);
// 	sig = SinOsc.ar(freq);
// 	sig = sig*amp*env;
// 	sig = Pan2.ar(sig, pan);
// 	Out.ar(0, sig);
// }).add;

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


//recebe ofOsc /of/updatePan/id, pan
//atualiza os synths
OSCdef.new(\updatePan, {
	arg msg;

	var id = msg[1].asInt;
	var pan = msg[2].asFloat;
	msg.postln;
	~numOfPartials.do({
			arg i;
		~arrayOfSynths[id][i].set(\pan, pan);
	})
},'/of/updatePan');


OSCdef.new(\closeOsc, {
	s.freeAll;
},'/of/closeOsc');


)

