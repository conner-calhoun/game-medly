import h3d.Vector;
import h2d.Graphics;
import h2d.Text;
import Water;
import Bubble;

@:enum
abstract Palette(Int) {
	var Purple = 0x5e315b;
	var PinkRed = 0xb0305c;
	var Dark = 0x272736;
	var LightBlue = 0x66ffe3;
	var Blue = 0x4da6ff;
}

class Game extends hxd.App {
	public static var inst:Game;

	var hello:h2d.Text;
	var time:Float;
	var g:h2d.Graphics;

	function sin(time:Float, angle:Float, speed:Float, freq:Float, amp:Float):Float {
		return (Math.sin(time * speed + angle * freq) * amp);
	}

	// TODO: Make length based on start and end point
	function drawWavyLine(startX:Float, y:Float, len:Int, t:Float) {
		var x = startX;

		g.lineStyle(1, cast(Palette.PinkRed, Int));
		for (i in 0...len) {
			var dx = x + i;

			var sinSum = (sin(t, i / len, 1.2, 25, 5) + sin(t, i / len, 3.1, 20, 4) + sin(t, i / len, 2.2, 32, 7));
			var dy = y + sinSum;

			g.lineTo(dx, dy);
		}
		g.endFill();
	}

	var water:Water;
	var bubble:Bubble;

	/**
	 * Called once at startup
	 */
	override function init() {
		// for loading sprites
		hxd.Res.initEmbed();
		s2d.scaleMode = LetterBox(640, 360);

		g = new h2d.Graphics(s2d);

		time = 0.0;

		bubble = new Bubble(s2d);
		bubble.init();

		water = new Water(s2d);
		water.init();
	}

	/**
	 * Called once per frame
	 * @param dt time since last frame
	 */
	override function update(dt:Float) {
		g.clear();

		time += dt;
		// drawWavyLine(10, 90, 620, time);

		// Draw background
		g.beginFill(cast(Palette.PinkRed, Int));
		g.drawRect(0, 0, s2d.width, s2d.height);

		bubble.update(dt, s2d.width / 2, 150, 120);
		water.update(dt, 0, s2d.height - 50, s2d.width, 50);
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
