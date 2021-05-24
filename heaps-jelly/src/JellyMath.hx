class JellyMath {
	public static function sin(time:Float, step:Float, speed:Float, freq:Float, amp:Float):Float {
		return (Math.sin(time * speed + step * freq) * amp);
	}
}
