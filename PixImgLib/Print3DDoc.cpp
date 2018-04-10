#ifdef _XXX

enum Print3DAnaglyphMode {
   Print3DAnaglyphBlueRed = 0,
   Print3DAnaglyphGray,
   Print3DAnaglyphColor,
   Print3DAnaglyphHalfColor,
   Print3DAnaglyphWoods,
   Print3DAnaglyphDubois,
}; 




void CPrint3DDoc::OnViewRightEye()
{
   // TODO: Add your command handler code here

   char szLeftFile[FILE_NAME_SIZE];
   char szRightFile[FILE_NAME_SIZE];
   char szOutFile[FILE_NAME_SIZE];
   int iAnaglyphMode;

   strcpy( szLeftFile, m_szImageFile );
   strcpy( szRightFile, m_szRightFile );
   strcpy( szOutFile, m_szStereoFile );
   

   // create anaglyph image file
   
   iAnaglyphMode = Print3DAnaglyphBlueRed; // blue and red
   iAnaglyphMode = Print3DAnaglyphGray; // gray
   iAnaglyphMode = Print3DAnaglyphColor; // color
   iAnaglyphMode = Print3DAnaglyphHalfColor; // half color
   iAnaglyphMode = Print3DAnaglyphWoods; // woods
   iAnaglyphMode = Print3DAnaglyphDubois; // false color

   iAnaglyphMode = Print3DAnaglyphColor;

   if( !bCreateStereoAnaglyph( iAnaglyphMode, szLeftFile, szRightFile, szOutFile ) ) {
      goto PIX_EXIT;
   }

   // --- Done ---
PIX_EXIT: 
   return;
}

#endif // _XXX