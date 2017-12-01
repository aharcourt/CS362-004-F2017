/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   public void testManualTest()
   {
	   System.out.println("\n>>>>>>>>>>>>>>>>>>> Manual Test <<<<<<<<<<<<<<<<<<\n");
	   
	   String[] testURLs = {
			   ("http://www.facebook.com"), 
			   ("www.facebook.com"), 
			   ("http:/256.256.256.256:-1/..?action=view"), 
			   ("http://125.125.125.125"), 
			   ("http://www.google.com:80/test1?action=view"),
			   ("http://www.aaa.com"),
			   ("http://0.0.0.0:80/test1?action=view"),
			   ("aaa"),
			   ("777"),
			   (""),
			   ("chrome.extension://google.com"),
			   ("http://www.someuniversity.edu:80/path?query_string"),
			   ("http://www.someuniversity:80/path"),
			   ("http://www.someuniversity:80/"),
			   ("http://www.someuniversity:80"),
			   ("httpwww.amazon.com"),
			   ("http://www.amazon"),
			   ("http://www.loooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong.com"),
			   ("htp://www.facebook.com\""),
			   ("http://0.0.0.0:0")	   
	   };
	   
	   String[] expectedResults = {
			   ("true"), 
			   ("true"), 
			   ("false"), 
			   ("true"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("false"),
			   ("false"),
			   ("false"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("true"),
			   ("false"),
			   ("false"),
			   ("false"),
			   ("false"),
			   ("true")
	   };
	   
	   int numOfTests = testURLs.length;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   for(int i = 0; i < numOfTests; i++){
		   System.out.println("Test URL: " + testURLs[i]);
		   System.out.println("Expected Result: " + expectedResults[i]+ "  Actual Result: " + urlVal.isValid(testURLs[i]));
	   }

	   
	   System.out.println("\n>>>>>>>>>>>>>>> Manual Test Finished <<<<<<<<<<<<<<<");
	   
	   
   }
   
   
   public void testPartitionScheme() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all schemes that we will be testing
	   ResultPair[] schemes = {
			   new ResultPair("http://", true),
			   new ResultPair("Ftp://", true),
			   new ResultPair("1http://", false),
			   new ResultPair("httP0+-.://", true),
			   new ResultPair("http_$!://", false),
			   new ResultPair("http", false),
			   new ResultPair("", true)
	   };
	   numTests = schemes.length;
	   
	   // Display Testing Header
	   System.out.println("\n>>>>>>>>>>>> Partition Test: URL Scheme <<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = schemes[i].item + "www.google.com";
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != schemes[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionAuthority() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all authorities that we will be testing
	   ResultPair[] authorities = {
			   new ResultPair("oregonstate.edu", true),
			   new ResultPair("www.10best.com", true),
			   new ResultPair("www.google.com/webhp", true),
			   new ResultPair("256.255.255.255", false),
			   new ResultPair(".0.0.0.0.", false),
			   new ResultPair("255.255.255.255", true),
			   new ResultPair("0.0.0.0", true),
			   new ResultPair("", false)
	   };
	   numTests = authorities.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>> Partition Test: URL Authority <<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://" + authorities[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != authorities[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionPort() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all ports that we will be testing
	   ResultPair[] ports = {
			   new ResultPair("", true),
			   new ResultPair(":8080", true),
			   new ResultPair(":0", true),
			   new ResultPair(":65535", true),
			   new ResultPair(":-1.", false),
			   new ResultPair("65536", false),
			   new ResultPair("8080", false),
			   new ResultPair("abcd", false)
	   };
	   numTests = ports.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>>>>> Partition Test: URL Port <<<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://www.google.com" + ports[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != ports[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionPath() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all paths that we will be testing
	   ResultPair[] paths = {
			   new ResultPair("", true),
			   new ResultPair("/path/path", true),
			   new ResultPair("Path/path", false),
			   new ResultPair("/path?/path", false),
			   new ResultPair("/path01/&path!", true)
	   };
	   numTests = paths.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>>>>> Partition Test: URL Path <<<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://www.google.com" + paths[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != paths[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testPartitionQuery() {  
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int numTests, failedTests = 0;
	   boolean testResult;
	   String testURL;
	   
	   // Create "Result Pairs" for all queries that we will be testing
	   ResultPair[] queries = {
			   new ResultPair("", true),
			   new ResultPair("?key=value", true),
			   new ResultPair("Key=value", false),
			   new ResultPair("?KeyValue", false),
			   new ResultPair("?key=value&key2=value2", true)
	   };
	   numTests = queries.length;
	   
	   // Display Testing Header
	   
	   System.out.println("\n>>>>>>>>>>>>>> Partition Test: URL Query <<<<<<<<<<<<<\n");
	  
	   // Check URLs against expected values
	   for(int i = 0; i < numTests; i++){
		   testURL = "http://www.google.com" + queries[i].item;
		   testResult = urlVal.isValid(testURL);
		   System.out.print("Testing URL " + testURL + " ...");
		   if (testResult != queries[i].valid) {
			   System.out.print(" >>> FAILED <<<");
			   failedTests++;
		   }
		   System.out.print("\n");
		   
	   }
	   
	   //Print Results
	   System.out.println("\n>>>>>>>> Testing Finished with " + failedTests + "/" + numTests + " Failures <<<<<<<<");
   }
   
   public void testIsValid(){  
	 System.out.println("\n>>>>>>>>>>>>>>>>>>>> Unit Test <<<<<<<<<<<<<<<<<<<\n");
	 int bugCount   = 0,    // counter to keep track of the bugs
	 loopCount1 = 100,  // counter for the first loop
	 loopCount2 = 0;    // counter for the second loop
	
	 //using this container to hold all of the failed URLs that should have passed
	 String[] urlFail = new String[loopCount1],
	
	 //using this container to hold all of the passing URLs that should have failed
	          urlPass = new String[loopCount1];
	
	 //I am seperating the incorrect and correct values for each corresponding segment of a URL
	
	 //all of the following values are correct and were derived from testIsValid() in the URLValidator_Correct file.
	 String[] correctQuery 	   = { 
	                                "?action=view", 
			                        "?action=edit&mode=down", 
			                        "", 
			                        "?set=true&bob=dylan&you=true" 
	 						 	  },
	
			  correctPort       = { 
			                        ":80", 
			                        ":90", 
			                        ":100", 
			                        ":3000", 
			                        ":8888" 
			                      },
			
			  correctOption     = { 
			                        "/test1", 
			                        "/t123", 
			                        "/$23", 
			                        "/test/", 
			                        "/$23/file" 
			                      },
			
			  correctScheme     = { 
			                        "http://", 
			                        "", 
			                        "ftp://", 
			                        "h3t://" 
			                      },
			
			  correctPath       = { 
			                        "/test", 
			                        "/t123", 
			                        "/$23", 
			                        "/test/", 
			                        "/test/next" 
			                      },
			
			  correctAuthority  = { 
			                        "www.google.com", 
			                        "google.com", 
			                        "go.com", 
			                        "go.au", 
			                        "0.0.0.0", 
			                        "255.255.255.255", 
			                        "255.com", 
			                        "go.cc" 
			                              },
			 
			 //all of the following values are incorrect and were derived from testIsValid() in the URLValidator_Correct file.
			  incorrectScheme = { 
			                      "3ht://",
			                      "http:", 
			                      "http:/", 
			                      "://", 
			                      "http/" 
			                    },
			
			  incorrectPath   = { 
			                      "/..", 
			                      "/../", 
			                      "/correctPath/to//file", 
			                      "//#" 
			                    },
			
			  incorrectPort   = { 
			                      ":-1", 
			                      ":8888a", 
			                      ":70000", 
			                      "22000" 
			                    },
			
			  incorrectAuth   = { 
			                      "www.google.1com", 
			                      "256.256.256.256", 
			                      "16.16.16.16.16", 
			                      "55.55.55", 
			                      ".255.255.255.255", 
			                      "192.68.102.10.", 
			                      "abc", 
			                      "abc.123" 
			                    },
			
			  incorrectOpt    = { 
			                      "/../", 
			                      "/#", 
			                      "/test//file" 
			                    };
			
	 int schemePosition, authPosition, portPosition, pathPosition, optionPosition, queryPosition;

	 for(int i = 0; i < loopCount1; i++) {
	      //Here I am randomizing the position of each segment of protocol using Math.random, and I typecast the result to an int to get rid of the decimal
	      optionPosition  = (int) (Math.floor(Math.random() * 5));
	      portPosition    = (int) (Math.floor(Math.random() * 5));
	      authPosition    = (int) (Math.floor(Math.random() * 8));
	      pathPosition    = (int) (Math.floor(Math.random() * 5));
	      queryPosition   = (int) (Math.floor(Math.random() * 4));
	      schemePosition  = (int) (Math.floor(Math.random() * 4));

	      //Parsing together a string using the valid options
	      String corrURL = correctScheme[schemePosition] + correctAuthority[authPosition] + correctPort[portPosition] + correctPath[pathPosition] + correctQuery[queryPosition];

	      UrlValidator legit =  new UrlValidator();
	      //passing in the string we made above to isValid. This should return a 0 for false or a 1 for true!
	      boolean verify = legit.isValid(corrURL);

	      //since we saved the result to a boolean, we can directly check if the string was counted as valid or invalid
	      if ( verify == false ){
	    	  urlFail[loopCount2] = corrURL; //saving the failed URL in our container
	    	  loopCount2++; //incrementing the counter to reflect the index of out urlFail array.
	    	  bugCount++; //since it is false, we count this as a bug and add it to the counter!
	      }

	 }

	 //Let the user know how many bugs were present
	 System.out.println("Bugs Present in valid URL testing: " + bugCount);
	 
	 System.out.println("\nBugged URLs:\n");
	
	 for ( int i=0; i< urlFail.length; i++){
		 if ( urlFail[i] != null ) System.out.println( "\n" + i + "- " + urlFail[i]);
	 }
	
	 System.out.println("\nSuccessful completion of testing valid URLs.\n");
	
	 //Reset our counters in order to test invalid URLs
	 bugCount   = 0;
	 loopCount2 = 0;
	
	 //making a string made of all valid components except for a single invalid component
	 for(int i = 0; i < loopCount1; i++) {
	       //picking a value in the corresponding array at random
	       pathPosition   = (int) (Math.floor(Math.random() * 5));
	       schemePosition = (int) (Math.floor(Math.random() * 4));
	       portPosition   = (int) (Math.floor(Math.random() * 5));
	       authPosition   = (int) (Math.floor(Math.random() * 8));
	       optionPosition = (int) (Math.floor(Math.random() * 5));
	       queryPosition  = (int) (Math.floor(Math.random() * 4));


	       //assigning index positions to the invalid components
	       int invalidSchemePos = (int) (Math.floor(Math.random() * 5)),
	           invalidOptPos    = (int) (Math.floor(Math.random() * 3)),
	           invalidPathPos   = (int) (Math.floor(Math.random() * 4)),
	           invalidAuthPos   = (int) (Math.floor(Math.random() * 8)),
	           invalidPortPos   = (int) (Math.floor(Math.random() * 4)),
	           invalidQueryPos  = (int) (Math.floor(Math.random() * 4));

	       //determine which component will be replaced
	       int switchIn = (int) (Math.floor(Math.random() * 4));

	       //Create a random string made up of valid URL pieces and one invalid piece
	       String corrURL = null;
	       if( switchIn == 0 ){  
	         //replace scheme
	         corrURL = incorrectScheme[invalidSchemePos] + correctAuthority[authPosition] + correctPort[portPosition] + correctPath[pathPosition] + correctQuery[queryPosition];
	       } else if( switchIn == 1 ){ 
	         //replace auth
	         corrURL = correctScheme[schemePosition] + incorrectAuth[invalidAuthPos] + correctPort[portPosition] + correctPath[pathPosition] + correctQuery[queryPosition];
	       } else if( switchIn == 2){ 
	         //replace port
	         corrURL = correctScheme[schemePosition] + correctAuthority[authPosition] + incorrectPort[invalidPortPos] + correctPath[pathPosition] + correctQuery[queryPosition];
	       } else if( switchIn == 3){ 
	         //replace path
	         corrURL = correctScheme[schemePosition] + correctAuthority[authPosition] + correctPort[portPosition] + incorrectPath[invalidPathPos] + correctQuery[queryPosition];
	       }
	       //please note that since no incorrect queries were provided in the original URL Validator Test file I have left them out here as well.

	       UrlValidator isLegit =  new UrlValidator();
	       //passing in the string we made above and checking to see what happens next
	       boolean verify = isLegit.isValid(corrURL);

	       if ( verify == true ) {
	             bugCount++;  //since verify should not be true, we count it as a bug         
	             urlPass[loopCount2] = corrURL; //store the bugged URL in our container
	             loopCount2++;  //moving to the next index in our URL array           
	           }
	   }

	   //show user the results
	   System.out.println("\nInvalid URLs that are considered valid:" + bugCount);
	   System.out.println("\nHere are the Invalid URLs that UrlValidator considered to be valid: \n");
	   for ( int i=0; i< urlFail.length; i++) {
		   if ( urlPass[i] != null ) System.out.println( "\n" + i + "- " + urlPass[i]);
	   }
	   
	   System.out.println("\n>>>>>>>>>>>>>>>> Unit Test Finished <<<<<<<<<<<<<<<<");

   }
   
}
