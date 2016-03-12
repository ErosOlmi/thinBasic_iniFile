'
' IniFile internal implementation
'

#INCLUDE "Win32Api.inc"

CLASS IniFile

  INSTANCE fileName AS STRING

  CLASS METHOD CREATE()
    fileName = ""
  END METHOD

  INTERFACE iIniFile
    INHERIT IUNKNOWN

    ' --

    METHOD SetFile( aFileName AS STRING )

      fileName = aFileName

    END METHOD

    METHOD GetFile() AS STRING

      METHOD = fileName

    END METHOD

    METHOD SetValue( section AS STRING, key AS STRING, value AS STRING )
      WritePrivateProfileString(section+"", key+"", value+"", fileName+"")
    END METHOD

    METHOD GetValue( section AS STRING, key AS STRING, defaultValue AS STRING ) AS STRING
      LOCAL value AS ASCIIZ * 8192

      GetPrivateProfileString(section+"", key+"", defaultValue+"", value, 8192, fileName+"")

      METHOD = value
    END METHOD

    METHOD GetSections(OPTIONAL sectionSeparator AS STRING) AS STRING

      LOCAL value AS STRING
      value = NUL$(32768)

      GetPrivateProfileString(BYVAL 0, BYVAL 0, BYVAL 0, BYVAL STRPTR(value), 32767, fileName+"")

      IF STRPTR(sectionSeparator) = 0 THEN
        sectionSeparator = ","
      END IF
      value = RTRIM$(value, $NUL)

      REPLACE $NUL WITH sectionSeparator IN value
      METHOD = value

    END METHOD

    METHOD GetSectionKeys(section AS STRING, OPTIONAL keySeparator AS STRING) AS STRING

      LOCAL value AS STRING
      value = NUL$(32768)
      GetPrivateProfileString(section+"", BYVAL 0, BYVAL 0, BYVAL STRPTR(value), 32767, fileName+"")

      IF STRPTR(keySeparator) = 0 THEN
        keySeparator = ","
      END IF
      value = RTRIM$(value, $NUL)
      REPLACE $NUL WITH keySeparator IN value

      METHOD = value

    END METHOD


  END INTERFACE

END CLASS
