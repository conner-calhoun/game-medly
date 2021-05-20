/**
 * Main game class
 */

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
	}

	/**
	 * Entry function
	 */
	public static function main() {
		inst = new Game();
	}
}
