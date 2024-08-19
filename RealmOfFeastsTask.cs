using System;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;

namespace RealmOfFeasts.Tasks
{
    public class RealmOfFeastsTask : Task, ITask
    {
        // Define a property to hold the message to be logged
        [Required]
        public string Message { get; set; }

        // Define a property to hold the output file path
        [Output]
        public string OutputFilePath { get; set; }

        // Override the Execute method to perform the task's work
        public override bool Execute()
        {
            try
            {
                // Log the message to the build output
                Log.LogMessage(MessageImportance.High, Message);

                // Perform some task-specific work here
                // For example, write the message to an output file
                System.IO.File.WriteAllText(OutputFilePath, Message);

                // Indicate that the task completed successfully
                return true;
            }
            catch (Exception ex)
            {
                // Log any exceptions that occur
                Log.LogErrorFromException(ex);
                return false;
            }
        }
    }
}
