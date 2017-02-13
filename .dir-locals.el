((c-mode . ((flycheck-c/c++-gcc-executable . "avr-gcc")
            (flycheck-gcc-args . ("-Os" "-DF_CPU=16000000" "-mmcu=atmega328p"))
            (flycheck-gcc-include-path . ("/usr/avr/include" "."))
            (flycheck-checker . c/c++-gcc))))
