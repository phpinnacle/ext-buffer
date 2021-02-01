--TEST--
Buffer fluent test
--SKIPIF--
<?php
if (!extension_loaded('buffer')) {
	echo 'skip';
}
?>
--FILE--
<?php
$buffer = new PHPinnacle\Buffer\ByteBuffer('abcd');

echo $buffer->append('e')->bytes() . \PHP_EOL;
echo $buffer->discard(1)->bytes() . \PHP_EOL;
?>
--EXPECT--
abcde
bcde
