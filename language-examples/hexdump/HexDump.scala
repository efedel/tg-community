import java.io.FileInputStream
/* TODO: remove the while loop, and avoid Unit returns when possible
   use http://www.scala-lang.org/api/current/index.html#scala.io.Source
   instead of the FileInputStream, although FileInputStream is used to 
   in the example to show calling a java library is easy 
*/

/**
 * Created by prole on 2/19/14.
 */
object HexDump {

  def dump(f: FileInputStream): Unit = {
    val blockSize = 1024
    val maxBytesPerRow = 16
    var i = 0

    // lambda is this printable?
    val isPrintable = (b: Byte) => (b >= 0x21 && b <= 0x7E)

    // lambda turn 16 bytes into what we want to see
    val displayData = (data: Array[Byte]) => {
      data.foreach{ b =>
        if (i % maxBytesPerRow == 0) printf("\n%09d: ", i)
        val display = if (isPrintable(b)) b.asInstanceOf[Char] else '.'
        printf("%02X(%c) ", b, display)
        i += 1
      }
    }

    every16(f){ data => displayData(data)}
  }

  def every16(fins: FileInputStream)(func: (Array[Byte]) => Unit): Unit = {
    var buf = new Array[Byte](16)
    var thereAreStillBytes: Int = 0
    while (thereAreStillBytes != -1) {
      thereAreStillBytes = fins.read(buf)
      func(buf)
    }
  }

  def main(args: Array[String]): Unit = {

    if (args.length > 0) {
      for (file <- args) {
        // println("file: "+ file) // DEBUG
        val fins = new FileInputStream(file)
        try {
          dump(fins)
        } finally {
          fins.close
        }
      }
    }
  }
}
