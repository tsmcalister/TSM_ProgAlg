# TSM_ProgAlg

# compiler

use g++ version > 9

# linking to freeimage

Compile freeimage from source and then copy the `.a` files to `/usr/lib/`

Then compile using `-lfreeimageplus -static` (This doesn't cover the header files) 