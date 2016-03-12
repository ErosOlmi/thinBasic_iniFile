'
' IniFile thinBASIC interface
'

#INCLUDE "IniFile_Implementation.inc"

' -----------------------------------------------------------------------------

FUNCTION IniFile_LoadSymbols() AS LONG

  LOCAL RetCode AS LONG
  LOCAL pIniFile AS LONG

  pIniFile = thinBasic_Class_Add("IniFile", 0)

  IF pIniFile THEN

    thinBasic_Class_AddMethod(pIniFile, "_Create", %thinBasic_ReturnNone , CODEPTR(IniFile_Create))
    thinBasic_Class_AddMethod(pIniFile, "SetKey", %thinBasic_ReturnString, CODEPTR(IniFile_SetKey))
    thinBasic_Class_AddMethod(pIniFile, "GetKey", %thinBasic_ReturnString, CODEPTR(IniFile_GetKey))
    thinBasic_Class_AddMethod(pIniFile, "GetSections", %thinBasic_ReturnString, CODEPTR(IniFile_GetSections))
    thinBasic_Class_AddMethod(pIniFile, "GetKeys", %thinBasic_ReturnString, CODEPTR(IniFile_GetKeys))

    FUNCTION = 0
  ELSE
    FUNCTION = 1
  END IF
END FUNCTION

' -----------------------------------------------------------------------------

SUB IniFile_Create(BYVAL pObject AS LONG)

  LOCAL fileName AS STRING

  IF thinBasic_CheckOpenParens_Mandatory() THEN
    thinBasic_ParseString fileName

    IF thinBasic_CheckCloseParens_Mandatory() AND thinBasic_ErrorFree() THEN

      REDIM oObject(1& TO 1&) AS iIniFile AT pObject
      oObject(1&) = CLASS "IniFile"
      oObject(1&).SetFile(fileName)

    END IF
  END IF

END SUB

' -----------------------------------------------------------------------------

FUNCTION IniFile_SetKey(BYVAL pObject AS LONG) AS STRING

  LOCAL section, key, value AS STRING
  REDIM oObject(1& TO 1&) AS iIniFile AT pObject

  IF thinBasic_CheckOpenParens_Mandatory() THEN
    thinBasic_ParseString section

    IF thinBasic_CheckComma_Mandatory() AND thinBasic_ErrorFree() THEN
      thinBasic_ParseString key

      IF thinBasic_CheckComma_Mandatory() AND thinBasic_ErrorFree() THEN
        thinBasic_ParseString value

        IF thinBasic_CheckCloseParens_Mandatory() AND thinBasic_ErrorFree() THEN
          oObject(1&).SetValue(section, key, value)

          FUNCTION = value
        END IF

      END IF

    END IF

  END IF

END FUNCTION

FUNCTION IniFile_GetKey(BYVAL pObject AS LONG) AS STRING

  LOCAL section, key, defaultValue AS STRING
  REDIM oObject(1& TO 1&) AS iIniFile AT pObject

  IF thinBasic_CheckOpenParens_Mandatory() THEN
    thinBasic_ParseString section

    IF thinBasic_CheckComma_Mandatory() AND thinBasic_ErrorFree() THEN
      thinBasic_ParseString key

      IF thinBasic_CheckComma_Optional() AND thinBasic_ErrorFree() THEN
        thinBasic_ParseString defaultValue
      END IF

      IF thinBasic_CheckCloseParens_Mandatory() AND thinBasic_ErrorFree() THEN
        FUNCTION = oObject(1&).GetValue(section, key, defaultValue)
      END IF

    END IF

  END IF

END FUNCTION

FUNCTION IniFile_GetSections(BYVAL pObject AS LONG) AS STRING

  LOCAL sectionSeparator AS STRING
  REDIM oObject(1& TO 1&) AS iIniFile AT pObject

  IF thinBasic_CheckOpenParens_Mandatory() THEN
    thinBasic_ParseString sectionSeparator

    IF thinBasic_CheckCloseParens_Mandatory() AND thinBasic_ErrorFree() THEN
      FUNCTION = oObject(1&).GetSections(sectionSeparator)
    END IF

  END IF

END FUNCTION

FUNCTION IniFile_GetKeys(BYVAL pObject AS LONG) AS STRING

  LOCAL section, keySeparator AS STRING
  REDIM oObject(1& TO 1&) AS iIniFile AT pObject

  IF thinBasic_CheckOpenParens_Mandatory() THEN
    thinBasic_ParseString section

    IF thinBasic_CheckComma_Mandatory() AND thinBasic_ErrorFree() THEN
      thinBasic_ParseString keySeparator

      IF thinBasic_CheckCloseParens_Mandatory() AND thinBasic_ErrorFree() THEN
        FUNCTION = oObject(1&).GetSectionKeys(section, keySeparator)
      END IF

    END IF

  END IF

END FUNCTION
