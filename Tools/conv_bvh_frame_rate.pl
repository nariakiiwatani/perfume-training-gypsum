# Convert BVH File's framerate
# usage: perl conv_bvh_length.pl infile outfile framerate
# author nariakiiwatani(nariakiiwatani@annolab.com)
# 2012-04-10

use utf8;

if(@ARGV < 3) {
	print "usage: perl conv_bvh_length.pl infile outfile framerate";
	exit;
}

$srcfile = $ARGV[0];
$dstfile = $ARGV[1];
$srctime = 1;
$dsttime = 1/$ARGV[2];

$srcframe = 0;
$dstframe = 0;
$elapsedrate = 0;
$deltarate = 0;

open(SRC, $srcfile);
open(DST, "> ".$dstfile);

$flag = 0;
while(<SRC>)
{
	$line = $_;

	if($flag > 0) {
		if($flag == 1) {
			@prev = split(/ /, $line);
			$elapsedrate = 0;
			$flag = 2;
		}
		elsif($flag == 2) {
			@data = split(/ /, $line);
			while($elapsedrate < 1) {
				for($i = 0; $i <= $#data; $i++) {
					if($i > 2) {
						$gap = $data[$i]-$prev[$i];
						if(abs($gap) > 180) {
							if($gap > 0) {
								$prev[$i] += 360;
							}
							else {
								$prev[$i] -= 360;
							}
						}
					}
					$mask = sprintf("%.6f", $prev[$i] + ($data[$i]-$prev[$i])*$elapsedrate);
					print DST $mask." ";
				}
				print DST "\n";
				$elapsedrate += $deltarate;
			}
			$elapsedrate -= 1;
			@prev = @data;
		}
	}
	else {
		if($line =~ /Frames: ([\.0-9]+)/) {
			$srcframe = $1;
		}
		elsif($line =~ /Frame Time: ([\.0-9]+)/) {
			$srctime = $1;
			$dstframe = $srctime*1/$dsttime*$srcframe;
			$deltarate = ($srcframe-1)/($dstframe-1);
			print DST "Frames: ".int($dstframe)."\n";
			print DST "Frame Time: ".$dsttime."\n";
			$flag = 1;
		}
		else {
			print DST $line;
		}
	}
}

close(SRC);
close(DST);
