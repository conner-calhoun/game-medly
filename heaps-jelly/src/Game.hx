/**
 * Main game class
 */

import h2d.Graphics;
import haxe.ds.Vector;
import h2d.Text;

typedef Node = {
	x:Float,
	y:Float
}

class Game extends hxd.App {
	public static var inst:Game;

	var hello:h2d.Text;
	var time:Float;
	var curveHeight:Float;
	var g:h2d.Graphics;

	function drawWavySegment() {}

	/**
	 * Pretty much copied from the h2d.Graphics api
	 */
	function drawCircle(cx:Float, cy:Float, radius:Float, nsegments = 0) {
		g.lineStyle(1, 0xFF00FF);

		if (nsegments == 0)
			nsegments = Math.ceil(Math.abs(radius * 3.14 * 2 / 4));
		if (nsegments < 3)
			nsegments = 3;
		var angle = Math.PI * 2 / nsegments;
		for (i in 0...nsegments + 1) {
			var a = i * angle;
			g.lineTo(cx + Math.cos(a) * radius, cy + Math.sin(a) * radius);
		}

		g.endFill();
	}

	/**
	 * Called once at startup
	 */
	override function init() {
		// for loading sprites
		hxd.Res.initEmbed();

		g = new h2d.Graphics(s2d);

		hello = new h2d.Text(hxd.res.DefaultFont.get(), s2d);
		hello.text = "Heaps Jelly";
		hello.setPosition(5.0, 5.0);

		curveHeight = 0.0;
		time = 0.0;
	}

	/**
	 * Called once per frame
	 * @param dt time since last frame
	 */
	override function update(dt:Float) {
		g.clear();

		time += dt;
		curveHeight = (Math.sin(time) * 100);

		// left segment
		g.lineStyle(1, 0xFF00FF);
		g.lineTo(10, 100);
		g.curveTo(50, 100 + curveHeight, 90, 100);

		// right segment
		g.lineStyle(1, 0xFF00FF);
		g.lineTo(90, 100);
		g.curveTo(130, 100 - curveHeight, 170, 100);

		g.endFill();

		drawCircle(250, 250, 50);
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
